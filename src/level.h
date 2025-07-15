#pragma once

#include "tile.h"
#include "resources.h"
#include "files.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Level {
  int id;
  TileGroup collision_tiles;
  TileGroup decoration_tiles;
} Level;

/* Init level */
Level initLevel(int id);
bool registerTileGroup(const char *group_id, const char *csv_path, TileGroup *destination);
bool registerSpritesheets();

void drawLevel(Level *lvl);

/* Cleanup Level */
void destroyLevel(Level *lvl);

