#include "tile.h"
#include "resources.h"
#include <raylib.h>

Tile createTile(const char *id, Vector2 pos) {
  Resource *rs = getResource(id);
  if(rs == NULL) {
    TraceLog(LOG_ERROR, "[TILES] Kunne ikke oprette tile id \"%s\"", id);
    return (Tile) { .resource = NULL, .pos = {}};
  }

  return (Tile) {
    .resource = rs,
    .pos = pos
  };
}

void drawTile(Tile *tile) {
  DrawTexture(tile->resource->texture, tile->pos.x, tile->pos.y, WHITE);
}
