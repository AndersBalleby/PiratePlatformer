#include "background.h"
#include "paths.h"
#include "resources.h"
#include <raylib.h>

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
