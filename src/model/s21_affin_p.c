#include "s21_affin_p.h"
#include "matrix_t/s21_matrix.h"
#include "s21_data_structure.h"
#include <stdio.h>
#include <stdlib.h>

#define CREATE 1
#define INPUT 2


void MoveAndRotateModel(data_t **object, affine_t* vector) {

  transformation_t* data_with_point = FactoryTransformation(object, vector);

  for (size_t i = 0; i != (*object)->vertices_count / 3; ++i) {
    InputDot(data_with_point);
    TransformateDot(data_with_point);
  }

  FreeBufferData(data_with_point);
  return;
}

transformation_t* FactoryTransformation(data_t** info, affine_t* vector) {
  transformation_t* base = malloc(1*sizeof(*base));

  base->pack = PackMatrices(FactoryAffine(vector), CreateDot());
  base->object = info;
  base->point = malloc(1*sizeof(*base->point));
  base->vertex_ind = calloc(1, sizeof(size_t));

  return base;
}

matrix_t* FactoryAffine(affine_t* data) {
  matrix_t* modificator_dot = CreateMatrix(4, 4);
  FillDiagonalOnes(&modificator_dot);
  AddRotateXYZ(&modificator_dot, data);
  AddMoveXYZ(&modificator_dot, data);
  return modificator_dot;
}


matrix_t* CreateDot() {
    return CreateMatrix(4, 1);
}

void InputDot(transformation_t* all_data) {
  for (size_t j = 0; j != 3; ++j, ++(*all_data->vertex_ind)) {
    all_data->point->xyz[j] = (*all_data->object)->vertex_array[*all_data->vertex_ind];
  }
  if (all_data->point) {
    all_data->pack->data->matrix[kX][0] = all_data->point->xyz[kX];
    all_data->pack->data->matrix[kY][0] = all_data->point->xyz[kY];
    all_data->pack->data->matrix[kZ][0] = all_data->point->xyz[kZ];
    all_data->pack->data->matrix[3][0] = 1.0;
  }
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


int Scale(data_t **A, affine_t* zoom) {
  int ret = 0;
  return ret;
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

void FillDiagonalOnes(matrix_t** m) {
  for (size_t i = 0; i != 4; ++i) (*m)->matrix[i][i] = 1.0;
}


matrices_t* PackMatrices(matrix_t* m, matrix_t*p) {
  matrices_t* pack = malloc(1*sizeof(*pack));
  pack->affine = m;
  pack->data = p;
  return pack;
}


matrix_t* CreateMatrix(size_t row, size_t column) {
    matrix_t* m = malloc(1*sizeof(*m));
    if (m) s21_create_matrix(row, column, m);
    return m;
}


void FreeBufferData(transformation_t* data) {
  s21_remove_matrix(data->pack->data);
  s21_remove_matrix(data->pack->affine);
  free(data->pack->data);
  free(data->pack->affine);
  free(data->pack);
  free(data->point);
  free(data->vertex_ind);
  free(data);
}

