#include <raylib.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 728
#define WINDOW_TITLE "Pirate Platformer"

int main(void) {
  TraceLog(LOG_INFO, "Indlæser spil");
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    
    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
