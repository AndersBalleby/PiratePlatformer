#pragma once

#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Level {
  int id;
  TileGroup *tiles;
} Level;

// Heap allokering
Level initLevel(int id);
void drawLevel(Level *lvl);

bool validatePath(const char *path);
int readCSVToMap(const char *filename, int rows, int cols, int map[rows][cols]);
