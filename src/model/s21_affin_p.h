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

int MoveX(data_t **A, double a); 
int MoveY(data_t **A, double a); 
int MoveZ(data_t **A, double a); 

int Scale(data_t **A, double zoom);

int Move(data_t **A, double a, int cord);
void RotationX(data_t *A, double angle);

#ifdef __cplusplus
}
#endif

#endif // MODEL_S21_AFFIN_P_H
