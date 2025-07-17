#include "camera.h"
#include <raylib.h>

CustomCamera initCamera() {
  return (CustomCamera) {
    .offset = (Vector2) {0, -100},
    .rect = (Rectangle) {CAMERA_X, CAMERA_Y, CAMERA_WIDTH, CAMERA_HEIGHT},
  };
}

void boxTargetCamera(CustomCamera *camera, Player *player) {
  /* Find spiller position ift camera */
  float player_screen_x = player->entity.position.x - camera->offset.x;
  float player_screen_y = player->entity.position.y - camera->offset.y;

  if(player_screen_x < camera->rect.x) {
    camera->offset.x = player->entity.position.x - camera->rect.x;
  } else if(player_screen_x > camera->rect.x + camera->rect.width) {
    camera->offset.x = player->entity.position.x - (camera->rect.x + camera->rect.width);
  }
}

void drawTileWithOffset(Tile *tile, Vector2 offset) {
  Vector2 screen_pos = {
    tile->pos.x - offset.x,
    tile->pos.y - offset.y,
  };

  DrawTexture(tile->resource->texture, (int) screen_pos.x, (int) screen_pos.y, WHITE);
}

void customDraw(CustomCamera *camera, Map *map, Player *player) {
  boxTargetCamera(camera, player);
  
  size_t i;
  for(i = 0; i < map->collision_tiles.tiles_size; ++i) {
    if(map->collision_tiles.tiles[i].active && map->collision_tiles.tiles[i].resource->is_loaded)
      drawTileWithOffset(&map->collision_tiles.tiles[i], camera->offset);
  }

  for(i = 0; i < map->decoration_tiles.tiles_size; ++i) {
    if(map->decoration_tiles.tiles[i].active && map->decoration_tiles.tiles[i].resource->is_loaded)
      drawTileWithOffset(&map->decoration_tiles.tiles[i], camera->offset);
  }

  for(i = 0; i < map->animated_tiles.tiles_count; ++i) {
    if(map->animated_tiles.anim_tiles[i].tile.active && map->animated_tiles.anim_tiles[i].tile.resource->is_loaded)
      drawTileWithOffset(&map->animated_tiles.anim_tiles[i].tile, camera->offset);
  }
}
