#ifndef MODEL_S21_AFFIN_P_H_
#define MODEL_S21_AFFIN_P_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "s21_data_structure.h"

typedef enum {
  kX = 0,
  kY,
  kZ
} kCord;

void AddMoveXYZ(matrix_t** affine, affine_t* data);
int Scale(data_t **A, affine_t* zoom);

void MoveAndRotateModel(data_t **A, affine_t* vector);
void RotationX(data_t *A, affine_t* angle);

matrix_t* FactoryAffine(affine_t* data);
matrix_t* CreateDot();
matrix_t* CreateMatrix(size_t row, size_t column);
void InputDot(data_t** object, size_t *vertex_ind, vertices_t* point, matrix_t *inp);
void TransformateDot(vertices_t *point, matrices_t* dataset, data_t **object, size_t vertex_ind);
matrices_t* FactoryMatrices(matrix_t*m, matrix_t*p);
void FreeBufferData(matrices_t* pack);

#ifdef __cplusplus
}
#endif

#endif // MODEL_S21_AFFIN_P_H
