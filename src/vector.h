#ifndef VECTOR_H
#define VECTOR_H

typedef union {
  float v[3];

  struct {
    float x;
    float y;
    float z;
  };
} Vector3;

typedef union {
  float v[2];

  struct {
    float x;
    float y;
  };
} Vector2;

#endif
