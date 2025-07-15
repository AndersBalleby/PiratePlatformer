#include "level.h"
#include <raylib.h>

#define ROWS 11
#define COLS 60

Level initLevel(int id) {
  int dataSize = 0;

  int map[ROWS][COLS];



  return (Level){.id = id, .tiles = NULL, .tiles_size = 0};
}

void drawLevel(Level *lvl) {

}

void destroyLevel(Level *lvl) {
    TraceLog(LOG_INFO, "[LEVEL] Level uinitialiseres");
}

