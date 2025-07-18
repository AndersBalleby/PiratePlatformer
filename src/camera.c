#include "camera.h"


#define CAMERA_X 300
#define CAMERA_Y 350
#define CAMERA_WIDTH 350
#define CAMERA_HEIGHT 350
#define CAMERA_OFFSET_X 0
#define CAMERA_OFFSET_Y -100
CustomCamera initCamera() {
  return (CustomCamera){
      .offset = (Vector2){CAMERA_OFFSET_X, CAMERA_OFFSET_Y},
      .rect = (Rectangle){CAMERA_X, CAMERA_Y, CAMERA_WIDTH, CAMERA_HEIGHT},
  };
}

void boxTargetCamera(CustomCamera *camera, Player *player) {
  /* Find spiller position ift camera */
  Vector2 player_pos = player->entity.position;

  float player_screen_x = player_pos.x - camera->offset.x;
  float player_screen_y = player_pos.y - camera->offset.y;

  if (player_screen_x < camera->rect.x) {
    camera->offset.x = player_pos.x - camera->rect.x;
  } else if (player_screen_x > camera->rect.x + camera->rect.width) {
    camera->offset.x = player_pos.x - (camera->rect.x + camera->rect.width);
  }
}

void drawTileWithOffset(Tile *tile, Vector2 offset) {
  Vector2 screen_pos = {
      tile->pos.x - offset.x,
      tile->pos.y - offset.y,
  };

  Texture2D tile_texture = tile->resource->texture;
  DrawTexture(tile_texture, (int) screen_pos.x, (int) screen_pos.y, WHITE);
}

void customDraw(CustomCamera *camera, Map *map, Player *player) {
  boxTargetCamera(camera, player);

  size_t i;
  Tile *tile = NULL;
  for(i = 0; i < map->bg_palm_group.tiles_count; ++i) {
    tile = &map->bg_palm_group.anim_tiles[i].tile; 
    if(tile->active && tile->resource->is_loaded) {
      drawTileWithOffset(tile, camera->offset);
    }
  }

  for(i = 0; i < map->coin_group.tiles_count; ++i) {
    tile = &map->coin_group.anim_tiles[i].tile;
    if(tile->active && tile->resource->is_loaded) {
      drawTileWithOffset(tile, camera->offset);
    }
  }


 for (i = 0; i < map->collision_tiles.tiles_size; ++i) {
    tile = &map->collision_tiles.tiles[i];
    if (tile->active && tile->resource->is_loaded)
      drawTileWithOffset(tile, camera->offset);
  }

  for (i = 0; i < map->decoration_tiles.tiles_size; ++i) {
    tile = &map->decoration_tiles.tiles[i];
    if (tile->active && tile->resource->is_loaded)
      drawTileWithOffset(tile, camera->offset);
  }

  for(i = 0; i < map->fg_palm_group.tiles_count; ++i) {
    tile = &map->fg_palm_group.anim_tiles[i].tile; 
    if(tile->active && tile->resource->is_loaded) {
      drawTileWithOffset(tile, camera->offset);
    }
  }

}
