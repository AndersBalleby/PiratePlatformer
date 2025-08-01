#include "ui.h"
#include "paths.h"
#include "resources.h"
#include <raylib.h>

UI initUI(void) {
  return (UI) {
    .font = LoadFont(FONT_PATH), 
    .hb = (HealthBar) {
      .resource = getResource("health_bar"),
      .ticks = 5,
    },
    .cc = (CoinCounter) {
      .resource = getResource("coin_counter"),
      .coins = 0,
    }
  };
}

void updateUI(UI *ui, size_t player_health, size_t coin_count) { 
  ui->hb.ticks = player_health;
  ui->cc.coins = coin_count;
}

#define BAR_MAX_WIDTH 152
#define BAR_HEIGHT 4
void drawUI(UI *ui, float player_health) {
  float current_health_ratio = player_health / 5.0f;
  float current_bar_width = BAR_MAX_WIDTH * current_health_ratio;

  DrawTexture(ui->hb.resource->texture, 15, 5, WHITE);
  DrawRectangle(49, 33, current_bar_width, BAR_HEIGHT, (Color){0xdc, 0x49, 0x49, 0xff});
  DrawTexture(ui->cc.resource->texture, 45, 50, WHITE);
  DrawTextEx(ui->font, TextFormat("%02i", ui->cc.coins), (Vector2) {75, 53}, 30.0f, 2.0f, BLACK);
}

void closeUI(UI *ui) {
  UnloadFont(ui->font);
}
