#include "map.h"
#include "paths.h"
#include <stdio.h>

Map createMap(int level_id) {
  /* Load resources and spritesheets */
  char buffer_path[128]; // Buffer til filstier ud fra level_id
  
  TileGroup terrain_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_TERRAIN, level_id, level_id);
  registerTileGroup("terrain", buffer_path, &terrain_group);
  
  TileGroup grass_group = {};
  snprintf(buffer_path, sizeof(buffer_path), CSV_PATH_GRASS, level_id, level_id);
  registerTileGroup("grass", buffer_path, &grass_group);

  return (Map){
    .level_id = level_id,
    .collision_tiles = terrain_group,
    .decoration_tiles = grass_group,
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

          /* Find ID fra Resources */
          char buffer[128];
          snprintf(buffer, sizeof(buffer), "%s_%d", group_id, value);

          /* Beregn vector position */
          Vector2 pos = {.x = j * TILE_SIZE, .y = i * TILE_SIZE};

          tiles[tiles_size++] = createTile(buffer, pos);
        }
      }
    }
  }

  out_group->id = group_id;
  out_group->tiles_size = tiles_size;
  memcpy(out_group->tiles, tiles, sizeof(Tile) * tiles_size);
}

void drawMap(Map *map) {
  /* Draw Decoration tiles */
  for (int i = 0; i < map->decoration_tiles.tiles_size; ++i) {
    Tile tile = map->decoration_tiles.tiles[i];
    DrawTexture(tile.resource->texture, tile.pos.x, tile.pos.y, WHITE);
  }

  /* Draw Collision tiles */
  for (int i = 0; i < map->collision_tiles.tiles_size; ++i) {
    Tile tile = map->collision_tiles.tiles[i];
    DrawTexture(tile.resource->texture, tile.pos.x, tile.pos.y, WHITE);
  }
}
