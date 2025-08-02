#include "game.h"
#include "audio.h"
#include "background.h"
#include "camera.h"
#include "entity.h"
#include "files.h"
#include "level.h"
#include "map.h"
#include "paths.h"
#include "resources.h"
#include "tile.h"
#include "ui.h"
#include <raylib.h>
#include <string.h>

bool loadResources() {
  /* Load alle single resources */
  if (loadResource("player", LoadTexture(SPRITE_PLAYER)) == NULL ||
      loadResource("crate", LoadTexture(SPRITE_CRATE)) == NULL ||
      loadResource("health_bar", LoadTexture(UI_HEALTH_BAR_PATH)) == NULL ||
      loadResource("coin_counter", LoadTexture(UI_COIN_PATH)) == NULL) {
    return false;
  }

  /* Load alle spritesheets */
  if (loadSpritesheet("terrain", SPRITESHEET_TERRAIN, 256, 256) == NULL ||
      loadSpritesheet("grass", SPRITESHEET_GRASS, 320, 64) == NULL ||
      loadSpritesheet("coins", SPRITESHEET_COINS, 128, 64) == NULL ||
      loadSpritesheet("constraint", SPRITESHEET_CONSTRAINTS, 128, 64) == NULL)
    return false;

  if (loadAnimation("player_run", ANIMATION_PLAYER_RUN) == NULL ||
      loadAnimation("player_idle", ANIMATION_PLAYER_IDLE) == NULL ||
      loadAnimation("player_fall", ANIMATION_PLAYER_FALL) == NULL ||
      loadAnimation("player_jump", ANIMATION_PLAYER_JUMP) == NULL ||
      loadAnimation("coins_silver", ANIMATION_COIN_SILVER) == NULL ||
      loadAnimation("coins_gold", ANIMATION_COIN_GOLD) == NULL ||
      loadAnimation("palm_bg", ANIMATION_PALM_BG) == NULL ||
      loadAnimation("palm_large", ANIMATION_PALM_LARGE) == NULL ||
      loadAnimation("palm_small", ANIMATION_PALM_SMALL) == NULL ||
      loadAnimation("enemy_explosion", ANIMATION_ENEMY_EXPLOSION) == NULL ||
      loadAnimation("enemy_run", ANIMATION_ENEMY_RUN) == NULL) {
    return false;
  }

  return true;
}

Game initGame() {
  const int START_LEVEL = 1;
  Game game = {};

  TraceLog(LOG_INFO, "[GAME] Indstiller game state og current level");
  TraceLog(LOG_INFO, "[GAME] Nuværende Level: \"%d\"", START_LEVEL);
  TraceLog(LOG_INFO, "[GAME] Indlæser resources");
  if (!loadResources()) {
    TraceLog(LOG_ERROR,
             "[GAME] Kunne ikke indlæse alle resources, afbryder init");
    return (Game){.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  /* Level */
  Level current_level = initLevel(START_LEVEL);
  if (current_level.id == -1) { // Tjek for fejl under level initialisering
    TraceLog(LOG_ERROR, "[GAME] Fejl under initialisering af level 0");

    return (Game){.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  /* Player */
  Player player = initPlayer(current_level.id);
  if (player.animations[0] == NULL) {
    TraceLog(LOG_ERROR, "[GAME] Fejl under initialisering af player struct");
    return (Game){.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  /* Custom Camera */
  CustomCamera camera = initCamera();

  /* Sky & Water */
  Sky sky = initSky();

  const int water_top = 780;
  const int level_width = 11 * TILE_SIZE;
  const int screen_width = GetScreenWidth();
  Water water = initWater(water_top, level_width, screen_width);
  
  Entity entities[MAX_ENTITIES] = {};
  size_t entity_count = 0;
  initEntities(entities, &entity_count, current_level.id);

  /* UI */
  UI ui = initUI();

  game.game_state = GAMESTATE_PLAYING;
  game.current_level = current_level;
  game.camera = camera;
  game.ui = ui;
  game.sky = sky;
  game.water = water;
  game.player = player;
  game.entity_count = entity_count;
  
  /* Copy entity structs */
  for(size_t i = 0; i < entity_count; ++i) {
    game.entities[i] = entities[i];
  }

  return game;
}

bool runGame(Game *game) { // Main game loop
  if (game->game_state == GAMESTATE_ERROR) {
    TraceLog(LOG_ERROR, "[GAME] Afslutter spil (GAMESTATE_ERROR)");
    return false; // exit game fra main loop
  }

  /* Updates */
  updateUI(&game->ui, game->player.entity.health, game->player.coins);
  updateTiles(game);
  updatePlayer(&game->player);
  updateEntities(game);
  updateWater(&game->water);

  /* Collision */
  horizontalMovementCollision(game);
  verticalMovementCollision(game);
  checkEnemyConstraints(game);
  checkEnemyCollision(game);

  /* Drawing */
  drawSky(&game->sky);
  drawGame(game);
  drawPlayer(&game->player, game->camera.offset);
  drawWater(&game->water);
  drawUI(&game->ui, game->player.entity.health);

  checkWaterBounds(game);


  return true;
}

void updateEntities(Game *game) {
  for(size_t i = 0; i < game->entity_count; ++i) {
    updateEntity(&game->entities[i]);
  }
}


void updateTiles(Game *game) {
  AnimatedTileGroup *animated_tiles[ANIMATED_TILES_SIZE] = {
      &game->current_level.map.bg_palm_group,
      &game->current_level.map.fg_palm_group,
      &game->current_level.map.coin_group};

  size_t total_tile_count = 0;
  for (size_t i = 0; i < ANIMATED_TILES_SIZE; ++i) {
    total_tile_count += animated_tiles[i]->tiles_count;

    for (size_t j = 0; j < animated_tiles[i]->tiles_count; ++j) {
      AnimatedTile *anim_tile = &animated_tiles[i]->anim_tiles[j];
      if (anim_tile->tile.resource->is_loaded)
        updateAnimatedTile(anim_tile);
    }
  }
}

void checkWaterBounds(Game *game) { 
  if(game->player.entity.position.y >= GetScreenHeight()) {
    respawnPlayer(&game->player);
  }
}

void drawGame(Game *game) {
  customDraw(&game->camera, &game->current_level.map, &game->player, game->entities, game->entity_count);
}

void checkEnemyCollision(Game *game) {
  Entity *entity = NULL;
  Player *player = &game->player;
  Map *map = &game->current_level.map;

  for(size_t i = 0; i < game->entity_count; ++i) {
    entity = &game->entities[i];
    if(CheckCollisionRecs(entity->collision_rect, player->entity.collision_rect)) {
      if(player->entity.direction.y > 0 && entity->alive) {
        killEntity(entity);
        player->entity.direction.y = PLAYER_KILL_JUMP_SPEED; // lille hop
        playSound(SOUND_STOMP);
      }
    }
  }
}

void checkEnemyConstraints(Game *game) {
  Entity *entity = NULL;
  Map *map = &game->current_level.map;
  
  for(size_t i = 0; i < game->entity_count; ++i) {
    entity = &game->entities[i];

    for(size_t j = 0; j < map->constraint_group.tiles_size; ++j) {
      if(CheckCollisionRecs(entity->collision_rect, map->constraint_group.tiles[j].collision_rect)) {
       reverseEntity(entity); 
      }
    }
  }
}

void horizontalMovementCollision(Game *game) {
  Player *player = &game->player;
  Rectangle *player_rect = &player->entity.collision_rect;
  Vector2 *player_direction = &player->entity.direction;
  Map *map = &game->current_level.map;

  // Opdater horizontal player direction value (x)
  player_rect->x += player_direction->x * player->entity.speed;

  size_t i = 0;
  TileGroup coll_tiles = map->collision_tiles;
  for (i = 0; i < coll_tiles.tiles_size; ++i) {
    handleHorizontalCollision(game, &coll_tiles.tiles[i]);
  }

  AnimatedTileGroup *fg_palm_group = &map->fg_palm_group;
  for (i = 0; i < fg_palm_group->tiles_count; ++i) {
    handleHorizontalCollision(game, &fg_palm_group->anim_tiles[i].tile);
  }

  TileGroup *crate_group = &map->crates_group;
  for(i = 0; i < crate_group->tiles_size; ++i) {
    handleHorizontalCollision(game, &crate_group->tiles[i]);
  }

  AnimatedTileGroup *coin_group = &map->coin_group;
  for (size_t i = 0; i < coin_group->tiles_count; ++i) {

    AnimatedTile *anim_tile = &coin_group->anim_tiles[i];
    if(!anim_tile->tile.active) continue;

    if (CheckCollisionRecs(anim_tile->tile.collision_rect, *player_rect)) {
      handleCoin(player, anim_tile);      
    }
  }
}

void handleHorizontalCollision(Game *game, Tile *tile) {
  Player *player = &game->player;
  Rectangle *player_rect = &player->entity.collision_rect;
  Vector2 *player_direction = &player->entity.direction;

  if (CheckCollisionRecs(tile->collision_rect, *player_rect)) {
    if (player_direction->x < 0) {
      player_rect->x = tile->collision_rect.x + tile->collision_rect.width;
    } else if (player_direction->x > 0) {
      player_rect->x = tile->collision_rect.x - player_rect->width;
    }
  }
}

void verticalMovementCollision(Game *game) {
  Player *player = &game->player;
  Rectangle *player_rect = &player->entity.collision_rect;
  Vector2 *player_direction = &player->entity.direction;
  Map *map = &game->current_level.map;

  applyGravity(player);
  player->on_ground = false;

  TileGroup coll_tiles = map->collision_tiles;
  size_t i = 0;
  for(i = 0; i < coll_tiles.tiles_size; ++i) {
    handleVerticalCollision(game, &coll_tiles.tiles[i]);
  }

  TileGroup crate_group = map->crates_group;
  for(i = 0; i < crate_group.tiles_size; ++i) {
    handleVerticalCollision(game, &crate_group.tiles[i]);
  }
 
  AnimatedTileGroup *fg_palm_group = &map->fg_palm_group;
  for(i = 0; i < fg_palm_group->tiles_count; ++i) {
    handleVerticalCollision(game, &fg_palm_group->anim_tiles[i].tile);
  }

  AnimatedTileGroup *coin_group = &map->coin_group;
  for (size_t i = 0; i < coin_group->tiles_count; ++i) {
    
    AnimatedTile *anim_tile = &coin_group->anim_tiles[i];
    if(!anim_tile->tile.active) continue;
    if (CheckCollisionRecs(anim_tile->tile.collision_rect, *player_rect)) {
      handleCoin(player, anim_tile);
    }
  }

  if (player->on_ground && player_direction->y < 0 || player_direction->y > 1) {
    player->on_ground = false;
  }

  if (player->on_ceiling && player_direction->y > 0) {
    player->on_ceiling = false;
  }
}

void handleVerticalCollision(Game *game, Tile *tile) {
  Player *player = &game->player;
  Rectangle *player_rect = &player->entity.collision_rect;
  Vector2 *player_direction = &player->entity.direction;

  if (CheckCollisionRecs(tile->collision_rect, *player_rect)) {
    if (player_direction->y > 0) {
      player_rect->y = tile->collision_rect.y - player_rect->height;

      player->on_ground = true;
      player_direction->y = 0;

    } else if (player_direction->y < 0) {
      player_rect->y = tile->collision_rect.y + tile->collision_rect.height;

      player_direction->y = 0;
      player->on_ceiling = true;
    }
  }
}


void initEntities(Entity out_list[MAX_ENTITIES], size_t *entity_count, int level_id) {
  int map[ROWS][COLS];
  Animation *enemy_run = getAnimation("enemy_run");
  
  char buffer[128];
  snprintf(buffer, sizeof(buffer), CSV_PATH_ENEMIES, level_id, level_id);

  if(readCSVToMap(buffer, map)) {
    for(size_t i = 0; i < 11; ++i) {
      for(size_t j = 0; j < 60; ++j) {
        int value = map[i][j];
        if(value != -1) {
          int y_offset = TILE_SIZE - enemy_run->resources[0]->texture.height;
          out_list[(*entity_count)++] = createEntity(ENEMY, (Vector2) {j * TILE_SIZE, (i * TILE_SIZE) + y_offset});;
        }
      }
    }
  }
}


Player initPlayer(int level_id) {
  Player player = {
      .entity = createEntity(PLAYER, (Vector2) {0,0}),
      .on_ground = false,
      .on_ceiling = false,
      .last_jump_time = 0.0f,
      .gravity = PLAYER_GRAVITY,
      .state = PLAYER_STATE_IDLE,
      .coins = 0,
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
    return (Player){};
  }

  return player;
}

void destroyGame(Game *game) {
  destroyLevel(&game->current_level);
  destroyWater(&game->water);
  closeUI(&game->ui);
}
