#include "tile.h"
#include <raylib.h>

Tile createTile(Texture2D texture, Vector2 pos) {
  return (Tile) {
    .texture = texture,
    .pos = pos
  };
}

void drawTile(Tile *tile) {
  DrawTexture(tile->texture, tile->pos.x, tile->pos.y, WHITE);
}
