#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include "vector.h"

typedef struct {
  int health;
  int max_health;
  int satiety;
  int max_satiety;

  bool grounded;
  bool mouse_lock;

  float movement_speed;
  float gravity;
  float jump_power;

  Item hotbar[9];
  Item backpack[27];
  ArmorItem armor[4];

  Vector3 position;
  Vector2 rotation;
  Vector3 velocity;
} Player;

#endif
