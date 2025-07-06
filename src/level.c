#include "level.h"
#include <raylib.h>

Level initLevel(int id) {
  return (Level) {.id = id};
}
