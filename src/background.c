#include "background.h"
#include "paths.h"
#include "resources.h"
#include "tile.h"
#include <raylib.h>

#define WATER_TILE_WIDTH 192
Water initWater(int top, int level_width, int screen_width) {
  Water water;
  int water_start = -screen_width;
  size_t tile_x_amount = (level_width + screen_width * 2) / WATER_TILE_WIDTH;
  
  water.tile_count = tile_x_amount;
  water.animation = loadAnimation("water", ANIMATION_WATER);
  
  water.water_tiles = (Tile *) malloc(sizeof(Tile) * tile_x_amount);
  for(size_t i = 0; i < tile_x_amount; ++i) {
    int x = i * WATER_TILE_WIDTH + water_start;
    int y = top;
    water.water_tiles[i] = createTile("water_0", (Vector2) {x, y});
  }
  return water;
}

static float water_frame_index = 0;
static const float water_animation_speed = 0.15;
void drawWater(Water *water) {
  for(size_t i = 0; i < water->tile_count; ++i) {
    drawTile(&water->water_tiles[i]);
  }
}

void updateWater(Water *water) {
  if((int) water_frame_index >= 4) {
    water_frame_index = 0;
  }

  for(size_t i = 0; i < water->tile_count; ++i) {
    water->water_tiles[i].resource = water->animation->resources[(int) water_frame_index];
  }
 
  water_frame_index += water_animation_speed;
}

void destroyWater(Water *water) {
  for(size_t i = 0; i < water->animation->count; ++i) {
    if(water->animation->resources[i]->is_loaded)
      unloadResource(water->animation->resources[i]);
  }

  free(water->water_tiles);
}

Sky initSky() {
  return (Sky) {
    .sky_top = loadResource("sky_top", LoadTexture(SPRITE_SKY_TOP)),
    .sky_middle = loadResource("sky_middle", LoadTexture(SPRITE_SKY_MIDDLE)),
    .sky_bottom = loadResource("sky_bottom", LoadTexture(SPRITE_SKY_BOTTOM)),
  };
}

void drawSky(Sky *sky) {
  /* top */
  DrawTexturePro(sky->sky_top->texture,
                 (Rectangle){0.0f, 0.0f, sky->sky_top->texture.width, sky->sky_top->texture.height},
                 (Rectangle){0.0f, 0.0f, 1280, (float) 800.0 / 1.25},
                 (Vector2){0,0},
                 0.0f,
                 WHITE);

  /* middle */
  DrawTexturePro(sky->sky_middle->texture,
                 (Rectangle){0.0f, 0.0f, sky->sky_middle->texture.width, sky->sky_middle->texture.height},
                 (Rectangle){0.0f, (float) 800 / 1.25, 1280, 100},
                 (Vector2){0.0},
                 0.0f,
                 WHITE);

  /* bottom */
  DrawTexturePro(sky->sky_bottom->texture,
                 (Rectangle){0.0f, 0.0f, sky->sky_bottom->texture.width, sky->sky_bottom->texture.height},
                 (Rectangle){0.0f, (float)(800.0 / 1.25) + 100, 1280, 800.0},
                 (Vector2){0, 0}, 0.0f, WHITE);
}
