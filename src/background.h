#pragma once

#include "resources.h"
#include "paths.h"
typedef struct Sky {
  Resource *sky_top;
  Resource *sky_bottom;
  Resource *sky_middle;
} Sky;

Sky initSky();
void drawSky(Sky *sky);
