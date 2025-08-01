#include "level.h"

Level initLevel(int id) {
  Map map = createMap(id);

  return (Level){
    .id = id,
    .map = map,
  };
}

void destroyLevel(Level *lvl) {
  TraceLog(LOG_INFO, "[LEVEL] Level uinitialiseres");
  unloadAllResources();
}
