#pragma once

#include "entity.h"
#include "map.h"

typedef struct CustomCamera {
  Rectangle rect;
  Vector2 offset;
} CustomCamera;

CustomCamera initCamera();
void boxTargetCamera(CustomCamera *camera, Player *player);
void drawTileWithOffset(Tile *tile, Vector2 offset);
void customDraw(CustomCamera *camera, Map *map, Player *player);
