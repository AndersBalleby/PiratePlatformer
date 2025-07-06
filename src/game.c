#include "game.h"
#include "level.h"
#include <raylib.h>

Game initGame() {
  TraceLog(LOG_INFO, "Indstiller game state og current level");
  
  Level current_level = initLevel(0);
  if(current_level.id == -1) {
    TraceLog(LOG_ERROR, "Fejl under initialisering af level 0");
    return (Game) {.game_state = GAMESTATE_ERROR, .current_level = {.id = -1} };
  }

  return (Game) {
    .game_state = GAMESTATE_PLAYING,
    .current_level = initLevel(0),
  };
}

bool runGame(Game *game) {
  if(game->game_state == GAMESTATE_ERROR) {
    TraceLog(LOG_ERROR, "Afslutter spil (GAMESTATE_ERROR)");
    return false; // exit game fra main loop
  }

  return true;
}

void drawMap(Game *game) {}
