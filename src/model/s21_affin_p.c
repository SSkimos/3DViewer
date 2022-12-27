#include "s21_affin_p.h"
#include "matrix_t/s21_matrix.h"

int MatrixRotateX(); 
int MatrixRotateY(); 
int MatrixRotateZ(); 


int MatrixScale(matrix_t *A, double zoom) {
  int ret = 0;
  if ((int) zoom != 0) {
    s21_mult_number(A, zoom);
  } else {
    ret = 1;
  }
  return ret;
}

int MatrixMove(matrix_t *A, double a, int cord) {
	for (int i = 0; i < A->rows; i++) A->matrix[i][cord] += a;
  return 0;
}

int MatrixMoveX(matrix_t *A, double a) {
  return MatrixMove(A, a, kX);
}

int MatrixMoveY(matrix_t *A, double a) {
  return MatrixMove(A, a, kY);
}

int MatrixMoveZ(matrix_t *A, double a) {
  return MatrixMove(A, a, kZ);
}

void RotationX(matrix_t *A, double angle) {
	for (int i = 0; i < A->rows; i++) {
		double temp_y = A->matrix[i][1];
		double temp_z = A->matrix[i][2];
		A->matrix[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
		A->matrix[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
	}
}
