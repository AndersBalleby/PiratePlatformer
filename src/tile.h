#pragma once

#include "resources.h"
#include <raylib.h>

#define MAX_TILES 1000

typedef struct Tile {
  Resource *resource;
  Vector2 pos;
} Tile;

typedef struct TileGroup {
  Tile tiles[MAX_TILES];
  int tiles_size;
} TileGroup;


Tile createTile(const char *id, Vector2 pos);
TileGroup createTileGroup();

void drawTile(Tile *tile);
