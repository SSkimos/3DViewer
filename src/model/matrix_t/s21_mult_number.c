#include <stdlib.h>

#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number) {
  if (!A) {
    return kError;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }
  return kOk;
}
