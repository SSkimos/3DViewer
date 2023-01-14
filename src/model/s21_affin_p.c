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

transformation_t* FactoryTransformation(data_t** info, affine_t* vector) {
  transformation_t* base = malloc(1*sizeof(*base));

  base->pack = PackMatrices(FactoryAffine(vector), CreateDot());
  base->object = info;
  base->point = malloc(1*sizeof(*base->point));
  base->vertex_ind = calloc(1, sizeof(size_t));

  return base;
}


void MoveAndRotateModel(data_t **object, affine_t* vector) {

  transformation_t* data_with_point = FactoryTransformation(object, vector);

  for (size_t i = 0; i != (*object)->vertices_count / 3; ++i) {
    InputDot(data_with_point);
    TransformateDot(data_with_point);
  }

  FreeBufferData(data_with_point->pack);
  return;
}

void TransformateDot(transformation_t* dataset) {
    matrix_t result_vector = {0};
    s21_mult_matrix(dataset->pack->affine, dataset->pack->data, &result_vector); 

    (*dataset->object)->vertex_array[*dataset->vertex_ind-3] = result_vector.matrix[kX][0];
    (*dataset->object)->vertex_array[*dataset->vertex_ind-2] = result_vector.matrix[kY][0];
    (*dataset->object)->vertex_array[*dataset->vertex_ind-1] = result_vector.matrix[kZ][0];

    s21_remove_matrix(&result_vector);
}


void RotationX(data_t *object, affine_t* angle) {
  /* for (int i = 0; i < A->rows; i++) {
     double temp_y = A->data[i][1];
     double temp_z = A->data[i][2];
     A->data[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
     A->data[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
     } */
}

matrix_t* CreateDot() {
    return CreateMatrix(4, 1);
}

matrix_t* CreateMatrix(size_t row, size_t column) {
    matrix_t* m = malloc(1*sizeof(*m));
    if (m) s21_create_matrix(row, column, m);
    return m;
}

void InputDot(transformation_t* data_with_point) {
  for (size_t j = 0; j != 3; ++j, ++(*data_with_point->vertex_ind)) {
    data_with_point->point->xyz[j] = (*data_with_point->object)->vertex_array[*data_with_point->vertex_ind];
  }
  if (data_with_point->point) {
    data_with_point->pack->data->matrix[kX][0] = data_with_point->point->xyz[kX];
    data_with_point->pack->data->matrix[kY][0] = data_with_point->point->xyz[kY];
    data_with_point->pack->data->matrix[kZ][0] = data_with_point->point->xyz[kZ];
    data_with_point->pack->data->matrix[3][0] = 1.0;
  }
  return;
}

void FillDiagonalOnes(matrix_t** m) {
  for (size_t i = 0; i != 4; ++i) (*m)->matrix[i][i] = 1.0;
}

matrix_t* FactoryAffine(affine_t* data) {
  matrix_t* modificator_dot = CreateMatrix(4, 4);
  FillDiagonalOnes(&modificator_dot);
  // AddRotate
  // AddMove
  AddRotateXYZ(&modificator_dot, data);
  AddMoveXYZ(&modificator_dot, data);
  return modificator_dot;
}

void AddRotateXYZ(matrix_t** affine, affine_t* data) {
  if (data->rotateX) {
    double rotate = data->rotateX / 10;
    (*affine)->matrix[0][0] = cos(rotate);
    (*affine)->matrix[0][1] = sin(rotate);
    (*affine)->matrix[1][0] =-sin(rotate);
    (*affine)->matrix[1][1] = cos(rotate);
  } 
}

void AddMoveXYZ(matrix_t** affine, affine_t* data) {
  (*affine)->matrix[kX][3] = data->moveX;
  (*affine)->matrix[kY][3] = data->moveY;
  (*affine)->matrix[kZ][3] = data->moveZ;
}

matrices_t* PackMatrices(matrix_t* m, matrix_t*p) {
  matrices_t* pack = malloc(1*sizeof(*pack));
  pack->affine = m;
  pack->data = p;
  return pack;
}

void FreeBufferData(matrices_t* pack) {
  s21_remove_matrix(pack->data);
  s21_remove_matrix(pack->affine);
  free(pack->data);
  free(pack->affine);
  free(pack);
}
