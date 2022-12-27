#ifndef MODEL_S21_AFFIN_P_H_
#define MODEL_S21_AFFIN_P_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "matrix_t/s21_matrix.h"
#include <math.h>

typedef enum {
  kX = 0,
  kY,
  kZ
} kCord;

int MatrixRotateX(); 
int MatrixRotateY(); 
int MatrixRotateZ(); 

int MatrixMoveX(matrix_t *A, double a); 
int MatrixMoveY(matrix_t *A, double a); 
int MatrixMoveZ(matrix_t *A, double a); 

int MatrixScale(matrix_t *A, double zoom);

int MatrixMove(matrix_t *A, double a, int cord);
void RotationX(matrix_t *A, double angle);

#ifdef __cplusplus
}
#endif

#endif // MODEL_S21_AFFIN_P_H
