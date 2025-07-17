#include "game.h"
#include "background.h"
#include "camera.h"
#include "entity.h"
#include "level.h"
#include "paths.h"
#include "resources.h"
#include "tile.h"
#include <raylib.h>

bool loadResources() {
  /* Load alle single resources */
  if (loadResource("player", LoadTexture(SPRITE_PLAYER)) == NULL) {
    return false;
  }

  /* Load alle spritesheets */
  if (loadSpritesheet("terrain", SPRITESHEET_TERRAIN, 256, 256) == NULL ||
      loadSpritesheet("grass", SPRITESHEET_GRASS, 320, 64) == NULL)
    return false;

  if (loadAnimation("player_run", ANIMATION_PLAYER_RUN) == NULL ||
      loadAnimation("player_idle", ANIMATION_PLAYER_IDLE) == NULL ||
      loadAnimation("player_fall", ANIMATION_PLAYER_FALL) == NULL ||
      loadAnimation("player_jump", ANIMATION_PLAYER_JUMP) == NULL) {
    return false;
  }

  return true;
}

Game initGame() {
  const int START_LEVEL = 0;

  TraceLog(LOG_INFO, "[GAME] Indstiller game state og current level");
  TraceLog(LOG_INFO, "[GAME] Nuværende Level: \"%d\"", START_LEVEL);
  TraceLog(LOG_INFO, "[GAME] Indlæser resources");
  if (!loadResources()) {
    TraceLog(LOG_ERROR,
             "[GAME] Kunne ikke indlæse alle resources, afbryder init");
    return (Game){.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  Level current_level = initLevel(START_LEVEL);
  if (current_level.id == -1) { // Tjek for fejl under level initialisering
    TraceLog(LOG_ERROR, "[GAME] Fejl under initialisering af level 0");

    return (Game){.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  Player player = initPlayer(current_level.id);
  if(player.animations[0] == NULL) {
    TraceLog(LOG_ERROR, "[GAME] Fejl under initialisering af player struct");
    return (Game) {.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  return (Game){
      .game_state = GAMESTATE_PLAYING,
      .current_level = current_level,
      .camera = initCamera(),
      .sky = initSky(),
      .water = initWater(780, (11 * TILE_SIZE), GetScreenWidth()),
      .player = player,
      .entity_count = 0,
  };
}

bool runGame(Game *game) { // Main game loop
  if (game->game_state == GAMESTATE_ERROR) {
    TraceLog(LOG_ERROR, "[GAME] Afslutter spil (GAMESTATE_ERROR)");
    return false; // exit game fra main loop
  }

  updatePlayer(&game->player);
  updateWater(&game->water);

  horizontalMovementCollision(game);
  verticalMovementCollision(game);

  drawSky(&game->sky);
  drawGame(game);
  drawPlayer(&game->player, game->camera.offset);
  drawEntities(game);
  drawWater(&game->water);

  return true;
}

void drawGame(Game *game) {
  customDraw(&game->camera, &game->current_level.map, &game->player);
}

void drawEntities(Game *game) {
  if (game->entity_count == 0)
    return;
  for (int i = 0; i < game->entity_count; ++i) {
    drawEntity(&game->entities[i]);
  }
}

void horizontalMovementCollision(Game *game) {
  Player *player = &game->player;
  TileGroup coll_tiles = game->current_level.map.collision_tiles;

  player->entity.collision_rect.x +=
      player->entity.direction.x * game->player.entity.speed;

  for (size_t i = 0; i < coll_tiles.tiles_size; ++i) {
    if (CheckCollisionRecs(coll_tiles.tiles[i].collision_rect,
                           player->entity.collision_rect)) {
      if (player->entity.direction.x < 0) {
        player->entity.collision_rect.x =
            coll_tiles.tiles[i].collision_rect.x +
            coll_tiles.tiles[i].collision_rect.width;
      } else if (player->entity.direction.x > 0) {
        player->entity.collision_rect.x = coll_tiles.tiles[i].collision_rect.x -
                                          player->entity.collision_rect.width;
      }
    }
  }
}

void verticalMovementCollision(Game *game) {
  Player *player = &game->player;
  TileGroup coll_tiles = game->current_level.map.collision_tiles;

  applyGravity(player);
  player->on_ground = false;

  for (size_t i = 0; i < coll_tiles.tiles_size; ++i) {
    if (CheckCollisionRecs(coll_tiles.tiles[i].collision_rect,
                           player->entity.collision_rect)) {
      if (player->entity.direction.y > 0) {
        player->entity.collision_rect.y = coll_tiles.tiles[i].collision_rect.y -
                                          player->entity.collision_rect.height;
        player->on_ground = true;
        player->entity.direction.y = 0;
      } else if (player->entity.direction.y < 0) {
        player->entity.collision_rect.y =
            coll_tiles.tiles[i].collision_rect.y +
            coll_tiles.tiles[i].collision_rect.height;
        player->entity.direction.y = 0;
        player->on_ceiling = true;
      }
    }
  }

  if (player->on_ground && player->entity.direction.y < 0 ||
      player->entity.direction.y > 1) {
    player->on_ground = false;
  }

  if (player->on_ceiling && player->entity.direction.y > 0) {
    player->on_ceiling = false;
  }
}

Player initPlayer(int level_id) {
  Player player = {
      .entity = createEntity(PLAYER),
      .on_ground = false,
      .on_ceiling = false,
      .last_jump_time = 0.0f,
      .gravity = PLAYER_GRAVITY,
      .state = PLAYER_STATE_IDLE,
  };

  /* Set player spawn pos */
  Vector2 spawn_player = getPlayerSpawnPos(level_id);
  player.entity.collision_rect.x = spawn_player.x;
  player.entity.collision_rect.y = spawn_player.y;

  /* Set player animations */
  player.animations[PLAYER_STATE_IDLE] = getAnimation("player_idle");
  player.animations[PLAYER_STATE_RUNNING] = getAnimation("player_run");
  player.animations[PLAYER_STATE_FALLING] = getAnimation("player_fall");
  player.animations[PLAYER_STATE_JUMPING] = getAnimation("player_jump");

  if (player.entity.animation == NULL) {
    TraceLog(LOG_ERROR, "[GAME] Kunne ikke oprette en player entity");
    return (Player) {};
  }

  return player;
}

void destroyGame(Game *game) {
  destroyLevel(&game->current_level);
  destroyWater(&game->water);
}
