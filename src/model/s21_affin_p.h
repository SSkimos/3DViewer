#ifndef MODEL_S21_AFFIN_P_H_
#define MODEL_S21_AFFIN_P_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include "s21_data_structure.h"

typedef enum {
  kX = 0,
  kY,
  kZ
} kCord;

int RotateX(); 
int RotateY(); 
int RotateZ(); 

int MoveX(data_t **A, affine_t* vector); 
int MoveY(data_t **A, affine_t* vector); 
int MoveZ(data_t **A, affine_t* vector); 
int Move(data_t **A, affine_t* vector);

int Scale(data_t **A, affine_t* zoom);

int MoveAndRotateModel(data_t **A, affine_t* vector);
void RotationX(data_t *A, affine_t* angle);

matrix_t* FactoryAffine(affine_t* data);
matrix_t* CreateDot(vertices_t* point);
void InputDot(vertices_t* point, matrix_t *inp);

#ifdef __cplusplus
}
#endif

#endif // MODEL_S21_AFFIN_P_H
