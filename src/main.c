#include <raylib.h>

#include "game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 728
#define WINDOW_TITLE "Pirate Platformer"

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  TraceLog(LOG_INFO, "Indlæser spillet");

  // Init game & assets
  Game game = initGame();

  if (game.game_state == GAMESTATE_ERROR || game.current_level.id == -1) {
    TraceLog(LOG_ERROR, "Fejl under initialisering af game");
    TraceLog(LOG_ERROR, "Afslutter programmet");
  } else { // Begynd game loop
    while (!WindowShouldClose()) {
      BeginDrawing();
      
      if(!runGame(&game)) {
        EndDrawing();
        break;
      }

      ClearBackground(BLACK);

      EndDrawing();
    }
  }

  CloseWindow();

  return 0;
}
