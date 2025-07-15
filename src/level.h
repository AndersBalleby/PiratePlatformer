#pragma once

#include "tile.h"
#include "resources.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Level {
  int id;
  Tile* tiles; // todo: refactor til TileGroup senere
  int tiles_size;
} Level;

Level initLevel(int id);
void drawLevel(Level *lvl);
void destroyLevel(Level *lvl);

bool validatePath(const char *path);
int readCSVToMap(const char *filename, int rows, int cols, int map[rows][cols]);
