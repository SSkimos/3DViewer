#ifndef MODEL_DATA_STRUCTURE_H_
#define MODEL_DATA_STRUCTURE_H_
#include "matrix_t/s21_matrix.h"

typedef struct facets {
	long double *vertexes; // f 2 3 4 51 2 31 .. array
	int v_in_facets; // size data
} polygon_t;

typedef struct data {
  unsigned int vertices_count; // size data
  unsigned int facets_count; // size data
  matrix_t matrix_3d; // 1 big matrix
  double* vertex_array;
  unsigned int* lines_array;
  unsigned int size;
  unsigned int size_v;
} data_t;

#endif // MODEL_DATA_STRUCTURE_H_
