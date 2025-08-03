#include "particles.h"
#include "paths.h"
#include "resources.h"
#include <raylib.h>
#include <string.h>

#define PARTICLE_COUNT 4
#define MAX_PARTICLES 64
static Particle particle_arr[MAX_PARTICLES] = {0};
static Animation *particle_animations[PARTICLE_COUNT];

void initParticles(void) {
  particle_animations[PARTICLE_JUMP] =
      loadAnimation("particle_jump", ANIMATION_PARTICLE_JUMP);
  particle_animations[PARTICLE_LAND] =
      loadAnimation("particle_land", ANIMATION_PARTICLE_LAND);
  particle_animations[PARTICLE_RUN] =
      loadAnimation("particle_run", ANIMATION_PARTICLE_RUN);
  particle_animations[PARTICLE_ENEMY_DEATH] = loadAnimation("particle_enemy_death", ANIMATION_PARTICLE_ENEMY_DEATH);
}

#define ANIMATION_SPEED 0.30f
void tickParticles(void) {
  for (size_t i = 0; i < MAX_PARTICLES; ++i) {
    if (particle_arr[i].active && particle_arr[i].animation != NULL) {
      float next_index = particle_arr[i].animation_index + ANIMATION_SPEED;

      if (next_index >= particle_arr[i].animation->count) {
        particle_arr[i].active = false;
      } else {
        particle_arr[i].animation_index = next_index;
      }
    }
  }
}

void drawParticles(Vector2 camera_offset) {
  for (size_t i = 0; i < MAX_PARTICLES; ++i) {
    Particle p = particle_arr[i];
    if (p.active && p.animation != NULL) {
      Vector2 screen_pos = {};
      if(strcmp(p.animation->id, "particle_enemy_death") == 0)
        screen_pos = (Vector2) {p.position.x - camera_offset.x, p.position.y};
      else
       screen_pos = (Vector2) {p.position.x - camera_offset.x, p.position.y - camera_offset.y};
      DrawTexture(p.animation->resources[(int)p.animation_index]->texture,
                  screen_pos.x, screen_pos.y, WHITE);
    }
  }
}

void spawnParticle(ParticleType type, Vector2 pos) {
  for (size_t i = 0; i < MAX_PARTICLES; ++i) {
    if (!particle_arr[i].active) {
      particle_arr[type] = (Particle){
          .animation = particle_animations[type],
          .position = pos,
          .animation_index = 0.0f,
          .active = true,
      };
    }
  }
}
