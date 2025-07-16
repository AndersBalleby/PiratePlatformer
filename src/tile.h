#pragma once

#include "resources.h"
#include <raylib.h>

#define MAX_TILES 150

typedef struct Tile {
  Resource *resource;
  Vector2 pos;
  Rectangle collision_rect;
} Tile;

typedef struct TileGroup {
  const char *id;
  Tile tiles[MAX_TILES];
  int tiles_size;
} TileGroup;


Tile createTile(const char *id, Vector2 pos);

void drawTile(Tile *tile);
