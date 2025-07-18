#pragma once

#include "resources.h"
#include <raylib.h>

#define MAX_TILES 150

typedef enum TileType {
  TILETYPE_TERRAIN,
  TILETYPE_COIN,
  TILETYPE_GRASS,
  TILETYPE_PALMS_BG,
  TILETYPE_PALMS_FG,
  TILETYPE_CRATE,
} TileType;

typedef struct Tile {
  Resource *resource;
  Vector2 pos;
  Rectangle collision_rect;
  TileType type;
  bool active;
} Tile;

typedef struct AnimatedTile {
  Tile tile;
  Animation *animation;
  float animation_index;
  float animation_speed;
} AnimatedTile;

typedef struct TileGroup {
  const char *id;
  Tile tiles[MAX_TILES];
  int tiles_size;
} TileGroup;

typedef struct AnimatedTileGroup {
  const char *id;
  AnimatedTile anim_tiles[MAX_TILES];
  size_t tiles_count;
} AnimatedTileGroup;

Tile createTile(const char *id, Vector2 pos, TileType type);
AnimatedTile createAnimatedTile(const char *rs_id, const char *anim_id, Vector2 pos, float animation_speed, TileType type);

void updateAnimatedTile(AnimatedTile *anim_tile);

void drawTile(Tile *tile);
