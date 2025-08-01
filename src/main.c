#include <raylib.h>

#include "audio.h"
#include "game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Pirate Platformer"

int main(void) {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  
  SetTargetFPS(60);
  TraceLog(LOG_INFO, "[MAIN] Indlæser spillet");

  // Init game & assets
  Game game = initGame();
  const bool show_fps = true;
  
  if (game.game_state == GAMESTATE_ERROR || game.current_level.id == -1) {
    TraceLog(LOG_ERROR, "Fejl under initialisering af game");
    TraceLog(LOG_ERROR, "Afslutter programmet");
  } else if(!initAudio()) {
    TraceLog(LOG_ERROR, "Fejl under initialisering af audio device");
    TraceLog(LOG_ERROR, "Afslutter programmet");
  } else { // Begynd game loop
    while (!WindowShouldClose()) {
      BeginDrawing();      

      handleMusic(game.game_state);
 
      if(!runGame(&game)) {
        EndDrawing();
        break;
      }

      if(show_fps)
        DrawFPS(20, 20);

      ClearBackground(BLACK);
      EndDrawing();
    }

    destroyGame(&game);
  }
  
  closeAudio();
  CloseWindow();

  return 0;
}
