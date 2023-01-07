#include <math.h>

#include "s21_matrix.h"

int s21_sum_sub(matrix_t *A, matrix_t *B, matrix_t *result, int plus) {
  if ((!result) || (!A) || (!B)) {
    return kError;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    return kCalculationError;
  } else if (((A->rows <= 0) || (A->columns <= 0))) {
    return kError;
  } else if (s21_create_matrix(A->rows, B->columns, result) != 0) {
    return kError;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (plus) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      } else {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return kOk;
}
