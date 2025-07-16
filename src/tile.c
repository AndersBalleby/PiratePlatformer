#include "tile.h"
#include "resources.h"
#include <raylib.h>

Tile createTile(const char *id, Vector2 pos) {
  Resource *rs = getResource(id);
  if(rs == NULL) {
    TraceLog(LOG_ERROR, "[TILES] Kunne ikke oprette tile id \"%s\"", id);
    return (Tile) { .resource = NULL, .pos = {}};
  }

  Rectangle collision_rect = {
    .x = pos.x,
    .y = pos.y,
    .width = rs->texture.width,
    .height = rs->texture.height,
  };

  return (Tile) {
    .resource = rs,
    .pos = pos,
    .collision_rect = collision_rect,
  };
}

void drawTile(Tile *tile) {
  DrawTexture(tile->resource->texture, tile->pos.x, tile->pos.y, WHITE);
}
