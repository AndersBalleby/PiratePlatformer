#pragma once

#include "tile.h"
#include "files.h"

#define ANIMATED_TILES_SIZE 2
typedef struct Map {
  int level_id;
  TileGroup collision_tiles;
  TileGroup decoration_tiles;
  AnimatedTileGroup animated_tiles[ANIMATED_TILES_SIZE];
} Map;

/* Create & load resources*/
Map createMap(int level_id);

void registerTileGroup(const char *group_id, const char *csv_path, TileGroup *out_group, TileType type);
void registerAnimatedTileGroup(const char *group_id, const char *csv_path, AnimatedTileGroup *out_group, TileType type);

/* Rendering */
void drawMap(Map *map);

/* Unload */
void unloadMap(Map *map);
