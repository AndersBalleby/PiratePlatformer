#pragma once

#include "resources.h"
#include "tile.h"
#include <raylib.h>

/* PLAYER STATS */
#define PLAYER_JUMP_SPEED    -16
#define PLAYER_KILL_JUMP_SPEED -12
#define PLAYER_JUMP_COOLDOWN 0.3
#define PLAYER_GRAVITY 0.8f
#define PLAYER_SPEED 8.0f
#define PLAYER_MAX_HEALTH 5
#define PLAYER_ANIMATION_SPEED 0.13


/* ENEMY STATS */
#define ENEMY_MAX_HEALTH 1
#define ENEMY_SPEED 5.0f
#define ENEMY_ANIMATION_SPEED 0.13
#define ENEMY_MAX_ANIMATIONS 6

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
  bool alive;
} Entity;

typedef struct Player {
  Animation *animations[4]; //idle, running, falling, jumping
  Entity entity; /* Indeholder members fra entity */
  size_t coins;
  bool on_ground;
  bool on_ceiling;
  double last_jump_time;
  float gravity;
  PlayerState state;
} Player;


/* ENTITY */
Entity createEntity(EntityType type, Vector2 pos);
void drawEntity(Entity *entity, Vector2 offset);
void updateEntity(Entity *entity);
void moveEntity(Entity *entity);
void reverseEntity(Entity *entity);
void animateEntity(Entity *entity);
void killEntity(Entity *entity);

/* PLAYER */
void updatePlayer(Player *player);
Vector2 getPlayerSpawnPos(int level_id);
void drawPlayer(Player *player, Vector2 offset);
void respawnPlayer(Player *player);

/* Input & Physics */
void handleCoin(Player *player, AnimatedTile *coin);
void getPlayerInput(Player *player);
void jump(Player *player);
void applyGravity(Player *player);
void updatePlayerState(Player *player);
void animatePlayer(Player *player);
