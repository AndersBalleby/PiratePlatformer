#include "tile.h"
#include "resources.h"
#include <raylib.h>
#include <string.h>

Tile createTile(const char *id, Vector2 pos, TileType type) {
  Resource *rs = getResource(id);
  if(rs == NULL) {
    TraceLog(LOG_ERROR, "[TILES] Kunne ikke oprette tile id \"%s\"", id);
    return (Tile) { .resource = NULL, .pos = {}};
  }

  int offset_x = 0;
  int offset_y = 0;

  switch (type) {
    case TILETYPE_CRATE:
      offset_y = -23;
      break;
    default:
      break;
  }

  Vector2 new_pos = {
    pos.x - offset_x,
    pos.y - offset_y,
  };

  Rectangle collision_rect = {
    .x = new_pos.x,
    .y = new_pos.y,
    .width = rs->texture.width,
    .height = rs->texture.height,
  };

  return (Tile) {
    .resource = rs,
    .pos = new_pos,
    .collision_rect = collision_rect,
    .type = type,
    .active = true,
  };
}

AnimatedTile createAnimatedTile(const char *rs_id, const char *anim_id, Vector2 pos, float animation_speed, TileType type) {
  int offset_x = 0;
  int offset_y = 0;

  switch (type) {
    case TILETYPE_PALMS_BG:
      offset_y = 64;
      break;
    case TILETYPE_PALMS_FG:
      if(strcmp(rs_id, "palm_small_0") == 0) {
        offset_y = 38;
      } else {
        offset_y = 64;
      }
    default:
      break;
  }

  Vector2 new_pos = {
    pos.x - offset_x,
    pos.y - offset_y,
  };
  
  Tile tile = createTile(rs_id, new_pos, type);
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
