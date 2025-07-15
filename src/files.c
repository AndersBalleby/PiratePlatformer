#include "files.h"
#include <raylib.h>

#define MAX_LINE_LENGTH 1024
int readCSVToMap(const char *filename, int rows, int cols,
                 int map[rows][cols]) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    TraceLog(LOG_ERROR, "[FILES] Fejl ved åbning af csv fil");
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
      TraceLog(LOG_ERROR, "[FILES] Forkert antal kolonner i række %d", row);
      fclose(file);
      return 0;
    }

    row++;
  }

  if (row != rows) {
    TraceLog(LOG_ERROR, "[FILES] Forkert antal rækker i filen %s", filename);
    fclose(file);
    return 0;
  }

  fclose(file);
  return 1;
}
