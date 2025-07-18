#pragma once

#include "resources.h"
#include "paths.h"
#include "tile.h"
#include <raylib.h>

typedef struct Water {
  Animation *animation;
  Tile *water_tiles;
  size_t tile_count;
} Water;

void updateWater(Water *water);
void drawWater(Water *water);
void destroyWater(Water *water);

Water initWater(int top, int level_width, int screen_width);

typedef struct Sky {
  Resource *sky_top;
  Resource *sky_bottom;
  Resource *sky_middle;
} Sky;

Sky initSky();
void drawSky(Sky *sky);
