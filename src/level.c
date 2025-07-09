#include "level.h"
#include <raylib.h>

#define ROWS 11
#define COLS 60
#define TILE_SIZE 64

Level initLevel(int id) {
  int dataSize = 0;

  int map[ROWS][COLS];

  // Indlæs CSV og tjek alle values.
  // Todo at lave videre her
  Texture2D terrain_tiles[16];
  Image terrain_img = LoadImage("../resources/terrain/terrain_tiles.png");
  int x = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      terrain_tiles[x++] = LoadTextureFromImage(
          ImageFromImage(terrain_img, (Rectangle){.height = TILE_SIZE,
                                                  .width = TILE_SIZE,
                                                  .x = j * TILE_SIZE,
                                                  .y = i * TILE_SIZE}));
    }
  }

  Tile *tiles = (Tile *)malloc(sizeof(Tile) * MAX_TILES);
  if (tiles == NULL) {
    return (Level){.id = -1, .tiles = NULL, .tiles_size = 0};
  }

  x = 0;
  if (readCSVToMap("../levels/0/level_0_terrain.csv", ROWS, COLS, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        if (value != -1) {
          tiles[x++] =
              (Tile){.texture = terrain_tiles[value],
                     .pos = (Vector2){.x = j * TILE_SIZE, .y = i * TILE_SIZE}};
        }
      }
    }
  }

  return (Level){.id = id, .tiles = tiles, .tiles_size = x};
}

void drawLevel(Level *lvl) {
  Tile _tile;
  for (int i = 0; i < lvl->tiles_size; ++i) {
    _tile = lvl->tiles[i];
    DrawTexture(_tile.texture, _tile.pos.x, _tile.pos.y, WHITE);
  }
}

#define MAX_LINE_LENGTH 1024
int readCSVToMap(const char *filename, int rows, int cols,
                 int map[rows][cols]) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Fejl ved åbning af fil");
    return 0;
  }

  char line[MAX_LINE_LENGTH];
  int row = 0;

  while (fgets(line, sizeof(line), file) && row < rows) {
    char *token;
    int col = 0;

    // Fjern evt. linjeskift
    line[strcspn(line, "\n")] = 0;

    token = strtok(line, ",");
    while (token && col < cols) {
      map[row][col] = atoi(token);
      token = strtok(NULL, ",");
      col++;
    }

    if (col != cols) {
      fprintf(stderr, "Fejl: forkert antal kolonner i række %d\n", row);
      fclose(file);
      return 0;
    }

    row++;
  }

  if (row != rows) {
    fprintf(stderr, "Fejl: forkert antal rækker i filen\n");
    fclose(file);
    return 0;
  }

  fclose(file);
  return 1;
}

void destroyLevel(Level *lvl) {
    TraceLog(LOG_INFO, "[FREE] Level uinitialiseres");

    int unloaded_ids[lvl->tiles_size];
    int x = 0;
    /* Dette skal ændres når resourcemanager bliver lavet */
    for (int i = 0; i < lvl->tiles_size; ++i) {
        bool found = false;
        for (int j = 0; j < x; ++j) {
            if (unloaded_ids[j] == lvl->tiles[i].texture.id) {
                found = true;
                break;
            }
        }

        if (!found) {
            UnloadTexture(lvl->tiles[i].texture);
            unloaded_ids[x++] = lvl->tiles[i].texture.id;
        }
    }

    free(lvl->tiles);
}


bool validatePath(const char *path) { return access(path, F_OK) == 0; }
