#pragma once

#include "entity.h"
#include "resources.h"
typedef struct HealthBar {
  Resource *resource;
  size_t ticks;
} HealthBar;

typedef struct CoinCounter {
  Resource *resource;
  size_t coins;
} CoinCounter;

typedef struct UI {
  Font font;
  HealthBar hb;
  CoinCounter cc;
} UI;

UI initUI(void);
void updateUI(UI *ui, size_t player_health, size_t coin_count);
void drawUI(UI *ui, float player_health);
void closeUI(UI *ui);
