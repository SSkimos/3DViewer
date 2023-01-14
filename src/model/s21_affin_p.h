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

void MoveAndRotateModel(data_t **A, affine_t* vector);

int AddScale(matrix_t** affine, affine_t* data);
void AddMoveXYZ(matrix_t** affine, affine_t* data);
void AddRotateXYZ(matrix_t** affine, affine_t* data);

void RemoveMatrix(matrix_t* m);
matrix_t* CreateMatrix(size_t row, size_t column);
void FreeBufferData(transformation_t* data);
void FillDiagonalOnes(matrix_t** m);

matrix_t* CreateDot();
void InputDot(transformation_t* data_with_point);
void TransformateDot(transformation_t* dataset);

matrix_t* FactoryAffine(affine_t* data);
matrices_t* PackMatrices(matrix_t*m, matrix_t*p);

transformation_t* FactoryTransformation(data_t** info, affine_t* vector);


#ifdef __cplusplus
}
#endif

#endif // MODEL_S21_AFFIN_P_H
