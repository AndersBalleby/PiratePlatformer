#pragma once
#include "game.h"
#include <stdbool.h>

#define MASTER_VOLUME 0.2f

typedef enum MusicType {
  MUSIC_LEVEL,
  MUSIC_OVERWORLD,
} MusicType;

typedef enum SoundType {
  SOUND_COIN,
  SOUND_HIT,
  SOUND_JUMP,
  SOUND_STOMP,
} SoundType;

/* Init og Close */
bool initAudio(void);
void closeAudio(void);

/* Afspilning - Musik */
void handleMusic(GameState state);
void loadMusic(void);
void checkAndPlay(MusicType type);
void stopMusic(void);

/* Afspilning - Lydeffekter */
void loadSounds(void);
void playSound(SoundType type);
