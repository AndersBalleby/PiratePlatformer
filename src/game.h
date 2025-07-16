#pragma once

#include "level.h"
#include "entity.h"
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
  Player player;
  Entity entities[15];
  int entity_count;
} Game;

/* Resources */
bool loadResources();

/* Game Logik */
Game initGame(void);

bool runGame(Game *game);
void drawGame(Game *game);

void destroyGame(Game *game);

/* Collision */
void horizontalMovementCollision(Game *game);
void verticalMovementCollision(Game *game);

/* Entities */
void drawPlayer(Player *player);
void drawEntities(Game *game);
