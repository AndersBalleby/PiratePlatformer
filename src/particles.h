#pragma once
#include "resources.h"

typedef enum ParticleType {
  PARTICLE_JUMP,
  PARTICLE_LAND,
  PARTICLE_RUN,
  PARTICLE_ENEMY_DEATH,
} ParticleType;

typedef struct Particle {
  Animation *animation;
  Vector2 position;
  float animation_index;
  bool active;
} Particle;

void initParticles(void);
void tickParticles(void);
void drawParticles(Vector2 camera_offset);
void spawnParticle(ParticleType type, Vector2 pos);


