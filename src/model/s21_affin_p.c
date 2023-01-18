#include "s21_affin_p.h"

#include <stdio.h>
#include <stdlib.h>

#include "matrix_t/s21_matrix.h"
#include "s21_data_structure.h"

int MoveAndRotateModel(data_t** object, affine_t* vector) {
  int err = 0;
  transformation_t* data_with_point = FactoryTransformation(object, vector);
  err = MemoryAllocateCheck(object, data_with_point);
  if (!err) {
    for (size_t i = 0; i != (*object)->vertices_count / 3; ++i) {
      InputDot(data_with_point);
      TransformateDot(data_with_point);
    }
    FreeBufferData(data_with_point);
  }
  return err;
}

int MemoryAllocateCheck(data_t** object, transformation_t* data_with_point) {
  int err = 1;
  if (object && data_with_point && data_with_point->point &&
      data_with_point->pack && data_with_point->vertex_ind) {
    err = 0;
  }
  return err;
}

transformation_t* FactoryTransformation(data_t** info, affine_t* vector) {
  transformation_t* base = malloc(1 * sizeof(*base));

  if (base) {
    base->pack = PackMatrices(FactoryAffine(vector), CreateDot());
    base->object = info;
    base->point = malloc(1 * sizeof(*base->point));
    base->vertex_ind = calloc(1, sizeof(size_t));
  }

  return base;
}

matrix_t* FactoryAffine(affine_t* data) {
  matrix_t* modificator_dot = CreateMatrix(4, 4);
  if (modificator_dot) {
    FillDiagonalOnes(&modificator_dot);
    AddRotateXYZ(&modificator_dot, data);
    AddMoveXYZ(&modificator_dot, data);
    AddScale(&modificator_dot, data);
  }
  return modificator_dot;
}

matrix_t* CreateDot() { return CreateMatrix(4, 1); }

void InputDot(transformation_t* all_data) {
  for (size_t j = 0; j != 3; ++j, ++(*all_data->vertex_ind)) {
    all_data->point->xyz[j] =
        (*all_data->object)->vertex_array[*all_data->vertex_ind];
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

  (*dataset->object)->vertex_array[*dataset->vertex_ind - 3] =
      result_vector.matrix[kX][0];
  (*dataset->object)->vertex_array[*dataset->vertex_ind - 2] =
      result_vector.matrix[kY][0];
  (*dataset->object)->vertex_array[*dataset->vertex_ind - 1] =
      result_vector.matrix[kZ][0];

  s21_remove_matrix(&result_vector);
}

void AddScale(matrix_t** affine, affine_t* data) {
  matrix_t result = {0};
  matrix_t* scale_matrix = CreateMatrix(4, 4);
  if (data->scale && scale_matrix && affine) {
    FillDiagonalOnes(&scale_matrix);
    scale_matrix->matrix[0][0] = data->scale / 100;
    scale_matrix->matrix[1][1] = data->scale / 100;
    scale_matrix->matrix[2][2] = data->scale / 100;
    s21_mult_matrix(*affine, scale_matrix, &result);
    for (size_t i = 0; i != 4; ++i) {
      for (size_t j = 0; j != 4; ++j) {
        (*affine)->matrix[i][j] = result.matrix[i][j];
      }
    }
    s21_remove_matrix(&result);
  }
  RemoveMatrix(scale_matrix);
}

matrix_t* AddRotateX(affine_t* data) {
  matrix_t* rotateX = CreateMatrix(4, 4);
  if (rotateX) {
    FillDiagonalOnes(&rotateX);
    if (data->rotateX) {
      double rotate = data->rotateX / 10;
      rotateX->matrix[1][1] = cos(rotate);
      rotateX->matrix[1][2] = -sin(rotate);
      rotateX->matrix[2][1] = sin(rotate);
      rotateX->matrix[2][2] = cos(rotate);
    }
  }
  return rotateX;
}

matrix_t* AddRotateY(affine_t* data) {
  matrix_t* rotateY = NULL;
  rotateY = CreateMatrix(4, 4);
  if (rotateY) {
    FillDiagonalOnes(&rotateY);
    if (data->rotateY) {
      double rotate = data->rotateY / 10;
      rotateY->matrix[0][0] = cos(-rotate);
      rotateY->matrix[0][2] = -sin(-rotate);
      rotateY->matrix[2][0] = sin(-rotate);
      rotateY->matrix[2][2] = cos(-rotate);
    }
  }
  return rotateY;
}

matrix_t* AddRotateZ(affine_t* data) {
  matrix_t* rotateZ = NULL;
  rotateZ = CreateMatrix(4, 4);
  if (rotateZ) {
    FillDiagonalOnes(&rotateZ);
    if (data->rotateZ) {
      double rotate = data->rotateY / 10;
      rotateZ->matrix[0][0] = cos(rotate);
      rotateZ->matrix[0][1] = -sin(rotate);
      rotateZ->matrix[1][0] = sin(rotate);
      rotateZ->matrix[1][1] = cos(rotate);
    }
  }
  return rotateZ;
}

void AddRotateXYZ(matrix_t** affine, affine_t* data) {
  if (!data->rotateX && !data->rotateY && !data->rotateZ) {
    return;
  }
  matrix_t* rotateX = AddRotateX(data);
  matrix_t* rotateY = AddRotateY(data);
  matrix_t* rotateZ = AddRotateZ(data);
  if (!rotateX || !rotateY || !rotateZ) return;
  matrix_t result = {0};
  matrix_t result2 = {0};
  s21_mult_matrix(rotateX, rotateY, &result2);
  s21_mult_matrix(rotateZ, &result2, &result);
  for (size_t i = 0; i != 4; ++i) {
    for (size_t j = 0; j != 4; ++j) {
      (*affine)->matrix[i][j] = result.matrix[i][j];
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&result2);
  RemoveMatrix(rotateX);
  RemoveMatrix(rotateY);
  RemoveMatrix(rotateZ);
}

void AddMoveXYZ(matrix_t** affine, affine_t* data) {
  if (affine) {
    (*affine)->matrix[kX][3] = data->moveX;
    (*affine)->matrix[kY][3] = data->moveY;
    (*affine)->matrix[kZ][3] = data->moveZ;
  }
}

void FillDiagonalOnes(matrix_t** m) {
  if (m)
    for (size_t i = 0; i != 4; ++i) (*m)->matrix[i][i] = 1.0;
}

matrices_t* PackMatrices(matrix_t* m, matrix_t* p) {
  matrices_t* pack = malloc(1 * sizeof(*pack));
  if (pack) {
    pack->affine = m;
    pack->data = p;
  }
  return pack;
}

matrix_t* CreateMatrix(size_t row, size_t column) {
  matrix_t* m = malloc(1 * sizeof(matrix_t));
  if (!m) exit(1);
  if (m) s21_create_matrix(row, column, m);
  return m;
}

void RemoveMatrix(matrix_t* m) {
  if (m) s21_remove_matrix(m);
  free(m);
}

void FreeBufferData(transformation_t* data) {
  if (data && data->pack && data->point && data->vertex_ind) {
    RemoveMatrix(data->pack->data);
    RemoveMatrix(data->pack->affine);
    free(data->pack);
    free(data->point);
    free(data->vertex_ind);
    free(data);
  }
}

affine_t* InitAffine(void) {
  affine_t* v = malloc(1 * sizeof(*v));
  if (v) {
    v->moveX = 0;
    v->moveY = 0;
    v->moveZ = 0;
    v->rotateX = 0;
    v->rotateY = 0;
    v->rotateZ = 0;
    v->scale = 0;
  }
  return v;
}
