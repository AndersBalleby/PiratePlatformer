#pragma once

#include "level.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum GameState {
  GAMESTATE_PLAYING, // Playing level
  GAMESTATE_TITLE,   // Title Screen
  GAMESTATE_ERROR    // Tjek fejl løbende
} GameState;

typedef struct Game {
  GameState game_state;
  Level current_level;
} Game;

Game initGame(void);
void destroyGame(Game *game);
bool runGame(Game *game);
void drawGame(Game *game);

