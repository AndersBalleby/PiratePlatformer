#pragma once

#include "entity.h"
#include "map.h"

#define CAMERA_X 300
#define CAMERA_Y 350
#define CAMERA_WIDTH 350
#define CAMERA_HEIGHT 350
typedef struct CustomCamera {
  Rectangle rect;
  Vector2 offset;
} CustomCamera;

CustomCamera initCamera();
void boxTargetCamera(CustomCamera *camera, Player *player);
void drawTileWithOffset(Tile *tile, Vector2 offset);
void customDraw(CustomCamera *camera, Map *map, Player *player);
