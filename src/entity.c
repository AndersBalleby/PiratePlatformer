#include "entity.h"
#include "files.h"
#include "paths.h"
#include "resources.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

Entity createEntity(EntityType type) {
  Vector2 pos = { .x = 0, .y = 0};
  Entity ret = {
    .type = type,
    .position = pos,
    .direction = (Vector2) {0, 0},
    .on_right = true,
  };

  Animation *animation = NULL;
  switch (type) {
    case PLAYER:

      animation = getAnimation("player_run");
      if(animation == NULL) {
        TraceLog(LOG_ERROR, "[ENTITY] Kunne ikke finde animation til player entity");
        return (Entity) { .animation = NULL };
      }

      ret.collision_rect = (Rectangle) {
        .x = pos.x,
        .y = pos.y,
        .width = animation->resources[0]->texture.width,
        .height = animation->resources[0]->texture.height,
      };
      
      ret.speed = PLAYER_SPEED;
      ret.health = PLAYER_MAX_HEALTH;
      ret.animation_index = 0;
      ret.animation = animation;
      
      break;
    case ENEMY: 
      // Todo
      break;
    default:
      TraceLog(LOG_ERROR, "[ENTITY] Kunne ikke oprette ukendt entity type: \"%d\"", type);
      return (Entity) { .animation = NULL };
  }

  return ret;
}

void updatePlayer(Player *player) {
  getPlayerInput(player);
  updatePlayerState(player);
  animatePlayer(player);

  player->entity.position.x = player->entity.collision_rect.x;
  player->entity.position.y = player->entity.collision_rect.y;
}

void getPlayerInput(Player *player) {
  if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    player->entity.direction.x = -1;
    player->entity.on_right = false;
  } else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    player->entity.direction.x = 1;
    player->entity.on_right = true;
  } else {
    player->entity.direction.x = 0;
  }

  if((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && player->on_ground) {
    jump(player);
  }
}

void animateEntity(Entity *entity) {
  TraceLog(LOG_FATAL, "[ENTITY] animateEntity er ikke implementeret endnu");
}

static int maxFrames[] = {5, 6, 1, 3};
void animatePlayer(Player *player) {
  player->entity.animation = player->animations[player->state];

  player->entity.animation_index = fmod(player->entity.animation_index + PLAYER_ANIMATION_SPEED, maxFrames[player->state]);  
}

void updatePlayerState(Player *player) {
  if(!(player->on_ground) && player->entity.direction.y > 0) {
    player->state = PLAYER_STATE_FALLING;
    return;
  } else if(!(player->on_ground) && player->entity.direction.y < 0) {
    player->state = PLAYER_STATE_JUMPING;
    return;
  }

  if(player->entity.direction.x == 0) {
    player->state = PLAYER_STATE_IDLE;
  } else if(player->entity.direction.x > 0 || player->entity.direction.x < 0) {
    player->state = PLAYER_STATE_RUNNING;
  }
}

void jump(Player *player) {
  player->entity.direction.y = PLAYER_JUMP_SPEED;
}

void applyGravity(Player *player) {
  player->entity.direction.y += player->gravity;
  player->entity.collision_rect.y += player->entity.direction.y;
}

#define ROWS 11 // Antal rows i CSV
#define COLS 60 // Antal cols i CSV
Vector2 getPlayerSpawnPos(int level_id) {
  int map[ROWS][COLS];
  
  char buffer[128];
  snprintf(buffer, sizeof(buffer), CSV_PATH_PLAYER_SPAWN, level_id, level_id);

  if(readCSVToMap(buffer, ROWS, COLS, map)) {
    for(size_t i = 0; i < ROWS; ++i) {
      for(size_t j = 0; j < COLS; ++j) {
        int value = map[i][j];
        
        if(value != -1) {
          return (Vector2) { .x = j * TILE_SIZE, .y = i * TILE_SIZE };
        }
      }
    }
  }

  TraceLog(LOG_WARNING, "[ENTITY] Kunne ikke finde en spawn position for player i level: \"%d\"");
  return (Vector2) { .x = 0, .y = 0 };
}

void drawPlayer(Player *player, Vector2 offset) {
  int tallest_frame_height = 56;
  Texture2D current_texture = player->entity.animation->resources[(int) player->entity.animation_index]->texture;
  int y_offset = tallest_frame_height - current_texture.height;

  Vector2 screen_pos = {player->entity.position.x - offset.x,
                        player->entity.position.y - offset.y + y_offset};

  Rectangle source = {0.0f, 0.0f, (float) -(current_texture.width), (float) current_texture.height};

  if(player->entity.on_right) {
    DrawTexture(current_texture, screen_pos.x, screen_pos.y, WHITE);
  } else {
    DrawTextureRec(current_texture, source, screen_pos, WHITE);
  }
}

void handleCoin(Player *player, AnimatedTile *coin) {
  coin->tile.active = false;
}

void drawEntity(Entity *entity) {
  if(entity == NULL) return;
  DrawTexture(entity->animation->resources[(int) entity->animation_index]->texture, entity->position.x, entity->position.y, WHITE);
}

