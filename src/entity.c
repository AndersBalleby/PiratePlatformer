#include "entity.h"
#include "resources.h"
#include <raylib.h>

Entity createEntity(EntityType type) {
  // TODO : Ændre spawn position 
  Vector2 pos = { .x = 0, .y = 0};
  Entity ret = {
    .type = type,
    .position = pos,
    .direction = (Vector2) {0, 0},
    .on_right = true,
  };

  Resource *rs = NULL;
  switch (type) {
    case PLAYER:

      rs = getResource("player");
      if(rs == NULL) {
        TraceLog(LOG_ERROR, "[ENTITY] Kunne ikke finde resource til player entity");
        return (Entity) { .rs = NULL };
      }

      ret.collision_rect = (Rectangle) {
        .x = pos.x,
        .y = pos.y,
        .width = rs->texture.width,
        .height = rs->texture.height,
      };

      ret.speed = PLAYER_SPEED;
      ret.health = PLAYER_MAX_HEALTH;
      ret.rs = rs;
      
      break;

    case ENEMY: 
      rs = getResource("enemy");
      if(rs == NULL) {
        TraceLog(LOG_ERROR, "[ENTITY] Kunne ikke finde resource til enemy entity");
        return (Entity) { .rs = NULL };
      }
      
      ret.collision_rect = (Rectangle) {
        .x = pos.x,
        .y = pos.y,
        .width = rs->texture.width,
        .height = rs->texture.height,
      };

      ret.speed = ENEMY_SPEED;
      ret.health = ENEMY_MAX_HEALTH;
      ret.rs = rs;

      break;
    default:
      TraceLog(LOG_ERROR, "[ENTITY] Kunne ikke oprette ukendt entity type: \"%d\"", type);
      return (Entity) { .rs = NULL };
  }

  return ret;
}

void updatePlayer(Player *player) {
  getPlayerInput(player);
  updatePlayerState(player);

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

void drawEntity(Entity *entity) {
  if(entity == NULL) return;

  DrawTexture(entity->rs->texture, entity->position.x, entity->position.y, WHITE);
}

