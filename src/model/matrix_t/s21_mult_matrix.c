#include <stdlib.h>

#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if ((!result) || (!B) || (!A)) {
    return kError;
  } else if ((A->columns != B->rows)) {
    return kCalculationError;
  } else if (s21_create_matrix(A->rows, B->columns, result) != 0) {
    return kError;
  } else if ((result->rows <= 0) || (result->columns <= 0)) {
    return kError;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < B->rows; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return kOk;
}

// You can only multiply
// two matrices if their
// dimensions are compatible ,
// which means the number
// of columns in the
// first matrix is the
// same as the number
// of rows in the
// second matrix.
// The product of A = m × k by B = k × n
// is a matrix C = m × n = A × B
// of size m × n whose elements are defined by the equation
// C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j)
// + ... + A(i,k) × B(k,j).
