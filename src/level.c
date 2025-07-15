#include "level.h"
#include "files.h"
#include "resources.h"
#include "tile.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define ROWS 11
#define COLS 60

Level initLevel(int id) {
  /* Load resources and spritesheets */
  if (!registerSpritesheets()) {
    TraceLog(LOG_ERROR, "[LEVELS] Var ikke i stand til at registrere alle spritesheets");
    return (Level){};
  }

  TileGroup terrain_group = {};
  TileGroup grass_group = {};
  registerTileGroup("terrain", "../levels/0/level_0_terrain.csv", &terrain_group);
  registerTileGroup("grass", "../levels/0/level_0_grass.csv", &grass_group);

  return (Level){
      .id = id,
      .collision_tiles = terrain_group,
      .decoration_tiles = grass_group
  };
}

bool registerSpritesheets() {
  if (loadSpritesheet("terrain", "../resources/terrain/terrain_tiles.png", 256, 256) == NULL ||
      loadSpritesheet("grass", "../resources/decoration/grass/grass.png", 320, 64) == NULL)
    return false;

  return true;
}

bool registerTileGroup(const char *group_id, const char *csv_path,
                       TileGroup *destination) {
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

  destination->id = group_id;
  destination->tiles_size = tiles_size;

  memcpy(destination->tiles, tiles, sizeof(Tile) * tiles_size);

  return true;
}

void drawLevel(Level *lvl) {
  /* Draw Decoration tiles */
  for (int i = 0; i < lvl->decoration_tiles.tiles_size; ++i) {

    Tile tile = lvl->decoration_tiles.tiles[i];
    DrawTexture(tile.resource->texture, tile.pos.x, tile.pos.y, WHITE);
  }


  /* Draw Collision tiles */
  for (int i = 0; i < lvl->collision_tiles.tiles_size; ++i) {

    Tile tile = lvl->collision_tiles.tiles[i];
    DrawTexture(tile.resource->texture, tile.pos.x, tile.pos.y, WHITE);
  }

  }

void destroyLevel(Level *lvl) {
  TraceLog(LOG_INFO, "[LEVEL] Level uinitialiseres");
  unloadAllResources();
}
