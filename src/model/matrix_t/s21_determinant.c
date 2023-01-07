#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if ((!A) || (!result)) {
    return kError;
  } else if (((A->rows <= 0) || (A->columns <= 0))) {
    return kError;
  } else if (A->rows != A->columns) {
    return kCalculationError;
  }

  *result = 0;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result = s21_easy_determ(A);
  } else if (A->rows == 3) {
    for (int k = 0; k < A->rows; k++) {
      double determ = 0.0;
      matrix_t tmp = {0};
      s21_crop(A, 0, k, &tmp);
      determ = s21_easy_determ(&tmp) * pow(-1, (0 + k));
      s21_remove_matrix(&tmp);
      *result += A->matrix[0][k] * determ;
    }
  } else {
    double tmpdeterm;
    for (int k = 0; k < A->rows; k++) {
      matrix_t tmp = {0};
      s21_crop(A, 0, k, &tmp);
      s21_determinant(&tmp, &tmpdeterm);
      s21_remove_matrix(&tmp);
      *result += A->matrix[0][k] * tmpdeterm * pow(-1, (0 + k));
    }
  }
  return kOk;
}

int s21_crop(matrix_t *A, int n, int b, matrix_t *result) {
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  int a = 0;
  int z = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if ((i != n) && (j != b)) {
        result->matrix[a][z] = A->matrix[i][j];
        z++;
        if (z == result->columns) {
          z = 0;
          a++;
        }
      }
    }
  }
  return 0;
}

double s21_easy_determ(matrix_t *A) {
  double determ =
      A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  return determ;
}
