#pragma once

#include "tile.h"
#include "resources.h"
#include "files.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Level {
  int id;
  Map map;
} Level;

/* Init */
Level initLevel(int id);

/* Cleanup */
void destroyLevel(Level *lvl);

