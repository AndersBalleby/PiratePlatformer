#pragma once
#include "game.h"
#include <stdbool.h>

#define MASTER_VOLUME 0.2f

typedef enum MusicType {
  MUSIC_LEVEL,
  MUSIC_OVERWORLD,
} MusicType; 

/* Init og Close */
bool initAudio(void);
void closeAudio(void);

/* Afspilning */
void handleMusic(GameState state);
void loadMusic(void);
void checkAndPlay(MusicType type);
void stopMusic(void);
