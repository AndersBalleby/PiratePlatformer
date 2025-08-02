#pragma once

#include "background.h"
#include "camera.h"
#include "level.h"
#include "entity.h"
#include "tile.h"
#include "ui.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum GameState {
  GAMESTATE_PLAYING, // Playing level
  GAMESTATE_TITLE,   // Title Screen
  GAMESTATE_ERROR    // Tjek fejl løbende
} GameState;

#define MAX_ENTITIES 15
typedef struct Game {
  GameState game_state;
  Level current_level;
  CustomCamera camera;
  UI ui;
  Sky sky;
  Water water;
  Player player;
  Entity entities[MAX_ENTITIES];
  size_t entity_count;
} Game;

/* Resources */
bool loadResources();

/* Game Logik */
Game initGame(void);
Player initPlayer(int level_id);

bool runGame(Game *game);
void drawGame(Game *game);

void destroyGame(Game *game);

/* Tiles */
void updateTiles(Game *game);

/* Collision */
void horizontalMovementCollision(Game *game);
void verticalMovementCollision(Game *game);
/* Til tiles */
void handleVerticalCollision(Game *game, Tile *tile);
void handleHorizontalCollision(Game *game, Tile *tile);
bool checkCoinCollision(Game *game);
void checkWaterBounds(Game *game);


/* Entities */
void initEntities(Entity out_list[MAX_ENTITIES], size_t *entity_count, int level_id);
void updateEntities(Game *game);
void checkEnemyConstraints(Game *game);
void checkEnemyCollision(Game *game);
