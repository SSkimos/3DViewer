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
void AddRotateXYZ(matrix_t** affine, affine_t* data);
int Scale(matrix_t** affine, affine_t* data);

void MoveAndRotateModel(data_t **A, affine_t* vector);
void RotationX(data_t *A, affine_t* angle);

void FillDiagonalOnes(matrix_t** m);
transformation_t* FactoryTransformation(data_t** info, affine_t* vector);
matrix_t* FactoryAffine(affine_t* data);
matrix_t* CreateDot();
matrix_t* CreateMatrix(size_t row, size_t column);
void InputDot(transformation_t* data_with_point);
void TransformateDot(transformation_t* dataset);
matrices_t* PackMatrices(matrix_t*m, matrix_t*p);
void FreeBufferData(transformation_t* data);

#ifdef __cplusplus
}
#endif

#endif // MODEL_S21_AFFIN_P_H
