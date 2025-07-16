#include "game.h"
#include "level.h"
#include <raylib.h>


Game initGame() {
  const int START_LEVEL = 0;
  TraceLog(LOG_INFO, "[GAME] Indstiller game state og current level");
  TraceLog(LOG_INFO, "[GAME] Current Level : \"%d\"", START_LEVEL);

  Level current_level = initLevel(START_LEVEL);
  
  if (current_level.id == -1) { // Tjek for fejl under level initialisering
    TraceLog(LOG_ERROR, "[GAME] Fejl under initialisering af level 0");

    return (Game){.game_state = GAMESTATE_ERROR, .current_level = {.id = -1}};
  }

  return (Game){
      .game_state = GAMESTATE_PLAYING,
      .current_level = current_level,
  };
}

bool runGame(Game *game) { // Main game loop
  if (game->game_state == GAMESTATE_ERROR) {
    TraceLog(LOG_ERROR, "[GAME] Afslutter spil (GAMESTATE_ERROR)");
    return false; // exit game fra main loop
  }

  drawGame(game);

  return true;
}

void drawGame(Game *game) {
 drawLevel(&game->current_level); 
}

void destroyGame(Game *game) {
  destroyLevel(&game->current_level);
}
