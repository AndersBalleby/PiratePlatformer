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
  if(readCSVToMap("../levels/0/level_0_terrain.csv", ROWS, COLS, map)) {
    for(int i = 0; i < ROWS; ++i) {
      for(int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        printf("%d", value);
      }
      printf("\n");
    }
  }

  return (Level) {.id = id, .tiles = NULL};
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

bool validatePath(const char *path) {
  return access(path, F_OK) == 0;
}
