#ifndef MODEL_DATA_STRUCTURE_H_
#define MODEL_DATA_STRUCTURE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#include "matrix_t/s21_matrix.h"

typedef struct data {
  unsigned int vertices_count;
  unsigned int facets_count;
  float* vertex_array;
  unsigned int* lines_array;

  float* base_vertex_array;
  unsigned int* base_lines_array;

  unsigned int size_f;
  unsigned int size_v;
  float max_vert;
  float min_vert;
} data_t;

typedef struct vertices {
  long double xyz[3];
} vertices_t;

typedef struct affine {
  double rotateX;
  double rotateY;
  double rotateZ;

  double moveX;
  double moveY;
  double moveZ;
  double scale;
} affine_t;

typedef struct matrices {
  matrix_t* affine;
  matrix_t* data;
} matrices_t;

typedef struct transformation {
  matrices_t* pack;
  size_t* vertex_ind;
  vertices_t* point;
  data_t** object;
} transformation_t;

#ifdef __cplusplus
}
#endif
#endif  // MODEL_DATA_STRUCTURE_H_
