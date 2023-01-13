#include "s21_affin_p.h"
#include "matrix_t/s21_matrix.h"
#include "s21_data_structure.h"
#include <stdio.h>
#include <stdlib.h>

#define CREATE 1
#define INPUT 2


int Scale(data_t **A, affine_t* zoom) {
  int ret = 0;
  return ret;
}
// 4*4 matrix of modif mult by 4x1 dot vector

void FactoryTransformationData(matrix_t* m, matrix_t*p, vertices_t*point, data_t*info);

int MoveAndRotateModel(data_t **A, affine_t* vector) {
  int f = 0;
  matrix_t result_vector = {0};
  vertices_t point = {0};
  matrix_t* m = FactoryAffine(vector);
  matrix_t* p = CreateDot(&point);
  matrices_t* pack = malloc(1*sizeof(*pack));
  pack->affine = m;
  pack->data = p;
  for (size_t i = 0; i != (*A)->vertices_count / 3; ++i) {
    for (size_t j = 0; j != 3; ++j) {
      point.xyz[j] = (long double) (*A)->vertex_array[f++];
    }
    InputDot(&point, p);
    TransformateDot(&point, pack, A, f);
    // s21_mult_matrix(m, p, &result_vector); 
    // (*A)->vertex_array[f-3] = result_vector.matrix[kX][0];
    // (*A)->vertex_array[f-2] = result_vector.matrix[kY][0];
    // (*A)->vertex_array[f-1] = result_vector.matrix[kZ][0];
    // s21_remove_matrix(&result_vector);
  }
  // 3 multiply matrix rotations
  // multiply them 
  // multiply other
  /* cos(a)  sin(a) 0
    -sin(a) cos(a) 0
    0       0      1
*/
  s21_remove_matrix(m);
  s21_remove_matrix(p);
  free(p);
  free(m);
  return 0;
}

void TransformateDot(vertices_t *point, matrices_t* dataset, data_t **A, int f) {
    matrix_t* affine = dataset->affine;
    matrix_t* data = dataset->data;
    matrix_t result_vector = {0};
    s21_mult_matrix(affine, data, &result_vector); 
    (*A)->vertex_array[f-3] = result_vector.matrix[kX][0];
    (*A)->vertex_array[f-2] = result_vector.matrix[kY][0];
    (*A)->vertex_array[f-1] = result_vector.matrix[kZ][0];
    s21_remove_matrix(&result_vector);
}


void RotationX(data_t *A, affine_t* angle) {
  /* for (int i = 0; i < A->rows; i++) {
     double temp_y = A->data[i][1];
     double temp_z = A->data[i][2];
     A->data[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
     A->data[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
     } */
}

matrix_t* CreateDot(vertices_t* point) {
    matrix_t* dot = {0};
    dot = malloc(1*sizeof(*dot));
    s21_create_matrix(4, 1, dot);
    return dot;
}
void InputDot(vertices_t* point, matrix_t *inp) {
  if (inp) {
    inp->matrix[kX][0] = point->xyz[kX];
    inp->matrix[kY][0] = point->xyz[kY];
    inp->matrix[kZ][0] = point->xyz[kZ];
    inp->matrix[3][0] = 1.0;
  }
  return;
}

matrix_t* FactoryAffine(affine_t* data) {
  matrix_t* modificator_dot = 0;
  modificator_dot = malloc(1*sizeof(*modificator_dot));
  s21_create_matrix(4, 4, modificator_dot);
  for (size_t i = 0; i != 4; ++i) modificator_dot->matrix[i][i] = 1.0;
  modificator_dot->matrix[kX][3] = data->moveX;
  modificator_dot->matrix[kY][3] = data->moveY;
  modificator_dot->matrix[kZ][3] = data->moveZ;
  return modificator_dot;
}
