#pragma once
#include "resources.h"

typedef enum ParticleType {
  PARTICLE_JUMP,
  PARTICLE_LAND,
  PARTICLE_RUN,
} ParticleType;

typedef struct Particle {
  Resource *resource;
  Animation *animation;
  Vector2 position;
  float animation_index;
  bool active;
} Particle;

void initParticles(void);
void tickParticles(void);
void drawParticles(Vector2 camera_offset);
void spawnParticle(ParticleType type, Vector2 pos);


