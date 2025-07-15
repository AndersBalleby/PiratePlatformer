#pragma once

#include <raylib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TILE_SIZE 64
typedef struct Resource {
  char *id;
  Texture2D texture;
  bool is_loaded;
} Resource;

#define MAX_RESOURCES 150
typedef struct ResourceCollection {
  Resource resources[MAX_RESOURCES];
  int size;
} ResourceCollection;

#define MAX_SPRITESHEET_RESOURCES 16
typedef struct Spritesheet {
  char *id;
  Resource *resources[MAX_SPRITESHEET_RESOURCES];
  int size;
} Spritesheet;

#define MAX_SPRITESHEETS 4
typedef struct SpritesheetCollection {
  Spritesheet spritesheets[4];
  int size;
} SpritesheetCollection;

/* RESOURCES */
Resource *loadResource(const char *id, Texture2D texture);
Resource *getResource(const char *id);

void unloadResource(Resource *resource);
void unloadResourceByID(const char *id);
void unloadAllResources();

/* SPRITESHEETS */
Spritesheet *loadSpritesheet(const char *id, const char *file_path, int size);
Spritesheet *getSpritesheet(const char *id);

void unloadSpritesheet(Spritesheet *spsheet);
void unloadSpritesheetByID(const char *id);
