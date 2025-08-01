#include "audio.h"
#include "paths.h"
#include <raylib.h>

#define MUSIC_COUNT 2
static Music music_arr[MUSIC_COUNT];
static Music currently_playing;

#define SOUND_COUNT 4
static Sound sound_arr[SOUND_COUNT];

bool initAudio(void) {
  InitAudioDevice();

  if (!IsAudioDeviceReady()) {
    return false;
  }

  loadMusic();
  loadSounds();
  SetMasterVolume(MASTER_VOLUME);
  return true;
}

void closeAudio(void) {
  size_t i;
  /* Unload Musik */
  for(i = 0; i < MUSIC_COUNT; ++i) {
    UnloadMusicStream(music_arr[i]);
  }
    
  /* Unload Lydeffekter */
  for(i = 0; i < SOUND_COUNT; ++i) {
    UnloadSound(sound_arr[i]);
  }

  CloseAudioDevice();
}

void handleMusic(GameState state) {
  switch (state) {
  case GAMESTATE_TITLE:
    checkAndPlay(MUSIC_OVERWORLD);
    break;
  case GAMESTATE_PLAYING:
    checkAndPlay(MUSIC_LEVEL);
    break;
  default:
    break;
  }
}

void loadMusic(void) {
  music_arr[MUSIC_LEVEL]     = LoadMusicStream(MUSIC_LEVEL_PATH);
  music_arr[MUSIC_OVERWORLD] = LoadMusicStream(MUSIC_OVERWORLD_PATH);
}

void loadSounds(void) {
  sound_arr[SOUND_COIN]  = LoadSound(SOUND_COIN_PATH);
  sound_arr[SOUND_HIT]   = LoadSound(SOUND_HIT_PATH);
  sound_arr[SOUND_JUMP]  = LoadSound(SOUND_JUMP_PATH);
  sound_arr[SOUND_STOMP] = LoadSound(SOUND_STOMP_PATH);
}

void playSound(SoundType type) {
  PlaySound(sound_arr[type]);
}


void checkAndPlay(MusicType type) {
  if (!IsMusicStreamPlaying(music_arr[type])) {
    stopMusic();

    PlayMusicStream(music_arr[type]);
    currently_playing = music_arr[type];
  } else {
    UpdateMusicStream(music_arr[type]);
  }
}

void stopMusic(void) {
  if (IsMusicStreamPlaying(currently_playing)) {
    StopMusicStream(currently_playing);
  }
}
