#pragma once

#include "entity.h"
#include "map.h"
#include "tile.h"

typedef struct CustomCamera {
  Rectangle rect;
  Vector2 offset;
} CustomCamera;

CustomCamera initCamera();
void boxTargetCamera(CustomCamera *camera, Player *player);
void drawTileWithOffset(Tile *tile, Vector2 offset);
void customDraw(CustomCamera *camera, Map *map, Player *player);
void drawAnimatedGroup(CustomCamera *camera, AnimatedTileGroup *group);
void drawGroup(CustomCamera *camera, TileGroup *group);
