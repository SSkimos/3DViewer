#include <stdlib.h>

#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if ((!result) || (!A)) {
    return kError;
  } else if (s21_create_matrix(A->rows, A->columns, result) != 0) {
    return kError;
  } else if ((result->rows <= 0) || (result->columns <= 0)) {
    return kError;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }
  return kOk;
}
