#include "game.h"
#include "level.h"
#include <raylib.h>

#define START_LEVEL 0

Game initGame() {
  TraceLog(LOG_INFO, "Indstiller game state og current level");

  Level current_level = initLevel(START_LEVEL);
  if (current_level.id == -1) { // Tjek for fejl under level initialisering
    TraceLog(LOG_ERROR, "Fejl under initialisering af level 0");

    return (Game){.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  return (Game){
      .game_state = GAMESTATE_PLAYING,
      .current_level = current_level,
  };
}

bool runGame(Game *game) { // Main game loop
  if (game->game_state == GAMESTATE_ERROR) {
    TraceLog(LOG_ERROR, "Afslutter spil (GAMESTATE_ERROR)");
    return false; // exit game fra main loop
  }

  drawMap(game);

  return true;
}

void drawMap(Game *game) {
 drawLevel(&game->current_level); 
}

void destroyGame(Game *game) {
  destroyLevel(&game->current_level);
}
