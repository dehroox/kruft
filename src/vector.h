#ifndef VECTOR_H
#define VECTOR_H

typedef union {
  double v[3];

  struct {
    double x;
    double y;
    double z;
  };
} Vector3;

typedef union {
  double v[2];

  struct {
    double x;
    double y;
  };
} Vector2;

#endif
