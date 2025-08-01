#include "audio.h"
#include "paths.h"
#include <raylib.h>

static Music music_arr[2];
static Music currently_playing;
bool initAudio(void) {
  InitAudioDevice();

  if (!IsAudioDeviceReady()) {
    return false;
  }

  loadMusic();
  SetMasterVolume(MASTER_VOLUME);
  return true;
}

void closeAudio(void) {
  UnloadMusicStream(music_arr[MUSIC_LEVEL]);
  UnloadMusicStream(music_arr[MUSIC_OVERWORLD]);
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
  music_arr[MUSIC_LEVEL] = LoadMusicStream(MUSIC_LEVEL_PATH);
  music_arr[MUSIC_OVERWORLD] = LoadMusicStream(MUSIC_OVERWORLD_PATH);
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
