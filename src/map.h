#pragma once

#include "tile.h"
#include "files.h"

typedef struct Map {
  int level_id;
  TileGroup collision_tiles;
  TileGroup decoration_tiles;
} Map;

/* Create & load resources*/
Map createMap(int level_id);

void registerTileGroup(const char *group_id, const char *csv_path, TileGroup *out_group);
bool registerSpritesheets(); 

/* Rendering */
void drawMap(Map *map);

/* Unload */
void unloadMap(Map *map);
