#pragma once

#include <raylib.h>

#define MAX_TILES 1000

typedef struct Tile {
  Texture2D texture;
  Vector2 pos;
} Tile;

typedef struct TileGroup {
  Tile tiles[MAX_TILES];
  int tiles_size;
} TileGroup;


Tile createTile(Texture2D texture, Vector2 pos);
TileGroup createTileGroup();

void drawTile(Tile *tile);
