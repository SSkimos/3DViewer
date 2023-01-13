#include "s21_affin_p.h"
#include "matrix_t/s21_matrix.h"
#include "s21_data_structure.h"
#include <stdio.h>


int Scale(data_t **A, affine_t* zoom) {
  int ret = 0;
  return ret;
}
// 4*4 matrix of modif mult by 4x1 dot vector
int MoveAndRotateModel(data_t **A, affine_t* vector) {
  int f = 0;
  matrix_t* m = FactoryAffine(vector);
  for (size_t i = 0; i != (*A)->vertices_count / 3; ++i) {
    for (size_t j = 0; j != 3; ++j) {
      // get 4x1 vector
      // mult vector
      // override vector
      // if (j % == 0) {
      //   (*A)->vertex_array[f] += a;
      //   printf("%f FLOATER\n ", (*A)->vertex_array[f]);
      //   f++;
      // }
    }
  }
  return 0;
}

int MoveX(data_t **A, affine_t* a) {
  return MoveAndRotateModel(A, a);
}

int MoveY(data_t **A, affine_t* a) {
  return MoveAndRotateModel(A, a);
}

int MoveZ(data_t **A, affine_t* a) {
  return MoveAndRotateModel(A, a);
}

void RotationX(data_t *A, affine_t* angle) {
  /* for (int i = 0; i < A->rows; i++) {
     double temp_y = A->data[i][1];
     double temp_z = A->data[i][2];
     A->data[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
     A->data[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
     } */
}

matrix_t* FactoryDot(vertices_t point) {
  matrix_t* dot = {0};
  s21_create_matrix(1, 4, dot);
  dot->matrix[0][kX] = point.xyz[kX];
  dot->matrix[0][kY] = point.xyz[kY];
  dot->matrix[0][kZ] = point.xyz[kZ];
  dot->matrix[0][3] = 1;
  return dot;
}

matrix_t* FactoryAffine(affine_t* data) {
  matrix_t* modificator_dot = {0};
  s21_create_matrix(4, 4, modificator_dot);
  return modificator_dot;
}
