#ifndef ITEM_H
#define ITEM_H

typedef struct {
  char *id;
  char *pretty_name;
  int amount;
} Item;

enum ArmorType { Feet, Leg, Chest, Head };

typedef struct {
  Item base;
  int armor_points;
  enum ArmorType type;
} ArmorItem;

#endif
