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
  registerTileGroup("terrain", buffer_path, &terrain_group);

  TileGroup grass_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_GRASS, level_id,
           level_id);
  registerTileGroup("grass", buffer_path, &grass_group);

  AnimatedTileGroup coins_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_COINS, level_id,
           level_id);
  registerAnimatedTileGroup("coins", buffer_path, &coins_group);

  return (Map){
      .level_id = level_id,
      .collision_tiles = terrain_group,
      .decoration_tiles = grass_group,
      .animated_tiles = coins_group,
  };
}

#define ROWS 11 // Antal rows i CSV
#define COLS 60 // Antal cols i CSV
void registerTileGroup(const char *group_id, const char *csv_path,
                       TileGroup *out_group) {
  Tile tiles[MAX_TILES];
  int tiles_size = 0;

  int map[ROWS][COLS];
  if (readCSVToMap(csv_path, ROWS, COLS, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        if (value != -1) {

          char buffer[128];
          Vector2 pos = {.x = j * TILE_SIZE, .y = i * TILE_SIZE};
          snprintf(buffer, sizeof(buffer), "%s_%d", group_id, value);

          tiles[tiles_size++] = createTile(buffer, pos);
        }
      }
    }
  }

  out_group->id = group_id;
  out_group->tiles_size = tiles_size;
  memcpy(out_group->tiles, tiles, sizeof(Tile) * tiles_size);
}

void registerAnimatedTileGroup(const char *group_id, const char *csv_path,
                               AnimatedTileGroup *out_group) {

  AnimatedTile tiles[MAX_TILES];
  size_t tiles_count = 0;

  int map[ROWS][COLS];
  int value = -1;
  if (readCSVToMap(csv_path, ROWS, COLS, map)) {
    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        value = map[i][j];
        if (value != -1) {

          char rs_buffer[128];
          char anim_buffer[128];
          Vector2 pos = {.x = j * TILE_SIZE, .y = i * TILE_SIZE};

          if (strcmp(group_id, "coins") == 0) {
            if (value == 0) {
              snprintf(rs_buffer, sizeof(rs_buffer), "%s_%d", "coins_gold", 0);
              strcpy(anim_buffer, "coins_gold");
            } else if (value == 1) {
              snprintf(rs_buffer, sizeof(rs_buffer), "%s_%d", "coins_silver", 0);
              strcpy(anim_buffer, "coins_silver");
            }
          }

          tiles[tiles_count++] = createAnimatedTile(rs_buffer, anim_buffer, pos, 0.15);
        }
      }
    }
  }

  out_group->id = group_id;
  out_group->tiles_count = tiles_count;
  memcpy(out_group->anim_tiles, tiles, sizeof(AnimatedTile) * tiles_count);

}
