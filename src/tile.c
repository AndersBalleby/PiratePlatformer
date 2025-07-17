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
    .active = true,
  };
}

AnimatedTile createAnimatedTile(const char *rs_id, const char *anim_id, Vector2 pos, float animation_speed) {
  Tile tile = createTile(rs_id, pos);
  if(tile.resource == NULL) {
    TraceLog(LOG_ERROR, "[TILES] Fejl under oprettelsen af animated tile med id: \"%s\"", anim_id);
    return (AnimatedTile) { .animation = NULL };
  }

  return (AnimatedTile) {
    .tile = tile,
    .animation = getAnimation(anim_id),
    .animation_index = 0.0,
    .animation_speed = animation_speed,
  };
}

void updateAnimatedTile(AnimatedTile *anim_tile) {
  if((int) anim_tile->animation_index >= anim_tile->animation->count) {
    anim_tile->animation_index = 0;
  }

  anim_tile->tile.resource = anim_tile->animation->resources[(int) anim_tile->animation_index];

  anim_tile->animation_index += anim_tile->animation_speed;
}

void drawTile(Tile *tile) {
  DrawTexture(tile->resource->texture, tile->pos.x, tile->pos.y, WHITE);
}
