#pragma once

#include "resources.h"
#include <raylib.h>

/* PLAYER STATS */
#define PLAYER_JUMP_SPEED    -16
#define PLAYER_JUMP_COOLDOWN 0.20f
#define PLAYER_GRAVITY 0.8f
#define PLAYER_SPEED 8.0f
#define PLAYER_MAX_HEALTH 5
#define PLAYER_ANIMATION_SPEED 0.13

/* ENEMY STATS */
#define ENEMY_MAX_HEALTH 1
#define ENEMY_SPEED 5.0f

typedef enum PlayerState {
  PLAYER_STATE_IDLE,
  PLAYER_STATE_RUNNING,
  PLAYER_STATE_FALLING,
  PLAYER_STATE_JUMPING,
} PlayerState;

typedef enum EntityType {
  PLAYER,
  ENEMY,
} EntityType;

typedef struct Entity {
  Animation *animation;
  Vector2 spawn_position;
  Vector2 position;
  Vector2 direction;
  Rectangle collision_rect;
  float speed;
  float animation_index;
  bool on_right;
  int health;
  EntityType type;
} Entity;

typedef struct Player {
  Animation *animations[4]; //idle, running, falling, jumping
  Entity entity; /* Indeholder members fra entity */
  bool on_ground;
  bool on_ceiling;
  float last_jump_time;
  float gravity;
  PlayerState state;
} Player;


/* ENTITY */
Entity createEntity(EntityType type);
void drawEntity(Entity *entity);
void updateEntity(Entity *entity);
void animateEntity(Entity *entity);

/* PLAYER */
void updatePlayer(Player *player);
Vector2 getPlayerSpawnPos(int level_id);
void drawPlayer(Player *player);

/* Input & Physics */
void getPlayerInput(Player *player);
void jump(Player *player);
void applyGravity(Player *player);
void updatePlayerState(Player *player);
void animatePlayer(Player *player);
