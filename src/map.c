#include "map.h"
#include "files.h"
#include "paths.h"
#include "tile.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

Map createMap(int level_id) {
  /* Load resources and spritesheets */
  char buffer_path[128]; // Buffer til filstier ud fra level_id

  TileGroup terrain_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_TERRAIN, level_id,
           level_id);
  registerTileGroup("terrain", buffer_path, &terrain_group, TILETYPE_TERRAIN);

  TileGroup grass_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_GRASS, level_id,
           level_id);
  registerTileGroup("grass", buffer_path, &grass_group, TILETYPE_GRASS);

  TileGroup crate_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_CRATE, level_id, level_id);
  registerTileGroup("crate", buffer_path, &crate_group, TILETYPE_CRATE);

  TileGroup constraint_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_CONSTRAINTS, level_id, level_id);
  registerTileGroup("constraint", buffer_path, &constraint_group, TILETYPE_CONSTRAINT);

  AnimatedTileGroup coins_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_COINS, level_id,
           level_id);
  registerAnimatedTileGroup("coins", buffer_path, &coins_group, TILETYPE_COIN);

  AnimatedTileGroup bg_palms_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_BG_PALMS, level_id, level_id);
  registerAnimatedTileGroup("palm_bg", buffer_path, &bg_palms_group, TILETYPE_PALMS_BG);

  
  AnimatedTileGroup fg_palms_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_FG_PALMS, level_id, level_id);
  registerAnimatedTileGroup("palm_fg", buffer_path, &fg_palms_group, TILETYPE_PALMS_FG);

  return (Map){
      .level_id = level_id,
      .collision_tiles = terrain_group,
      .decoration_tiles = grass_group,
      .crates_group = crate_group,
      .constraint_group = constraint_group,
      .coin_group = coins_group,
      .bg_palm_group = bg_palms_group,
      .fg_palm_group = fg_palms_group,
  };
}

void registerTileGroup(const char *group_id, const char *csv_path,
                       TileGroup *out_group, TileType type) {
  Tile tiles[MAX_TILES];
  int tiles_size = 0;

  int map[ROWS][COLS];
  if (readCSVToMap(csv_path, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        if (value != -1) {

          char buffer[128];
          Vector2 pos = {.x = j * TILE_SIZE, .y = i * TILE_SIZE};
          if(type == TILETYPE_CRATE) {
            snprintf(buffer, sizeof(buffer), "%s", group_id);
          } else {
            snprintf(buffer, sizeof(buffer), "%s_%d", group_id, value);
          }

          tiles[tiles_size++] = createTile(buffer, pos, type);
        }
      }
    }
  }

  out_group->id = group_id;
  out_group->tiles_size = tiles_size;
  memcpy(out_group->tiles, tiles, sizeof(Tile) * tiles_size);
}

void registerAnimatedTileGroup(const char *group_id, const char *csv_path,
                               AnimatedTileGroup *out_group, TileType type) {

  AnimatedTile tiles[MAX_TILES];
  size_t tiles_count = 0;
  int map[ROWS][COLS];
  int value = -1;
  if (readCSVToMap(csv_path, map)) {
    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        value = map[i][j];
        if (value != -1) {

          char rs_buffer[128];
          char anim_buffer[128];
          Vector2 pos = {.x = j * TILE_SIZE, .y = i * TILE_SIZE};

          if (strcmp(group_id, "coins") == 0) { /* COINS GROUP */
            if (value == 0) {
              strcpy(rs_buffer, "coins_gold_0");
              strcpy(anim_buffer, "coins_gold");
            } else if (value == 1) {
              strcpy(rs_buffer, "coins_silver_0");
              strcpy(anim_buffer, "coins_silver");
            }
          } else if(strcmp(group_id, "palm_bg") == 0) { /* BG PALMS GROUP */
            strcpy(rs_buffer, "palm_bg_0");
            strcpy(anim_buffer, group_id);
          } else if(strcmp(group_id, "palm_fg") == 0) {
            if(value == 0) {
              strcpy(rs_buffer, "palm_small_0");
              strcpy(anim_buffer, "palm_small");
            } else if(value == 1) {
              strcpy(rs_buffer, "palm_large_0");
              strcpy(anim_buffer, "palm_large");
            }
          }

          tiles[tiles_count++] = createAnimatedTile(rs_buffer, anim_buffer, pos, 0.15, type);
        }
      }
    }
  }

  out_group->id = group_id;
  out_group->tiles_count = tiles_count;
  memcpy(out_group->anim_tiles, tiles, sizeof(AnimatedTile) * tiles_count);
}
