#include <math.h>

#include "s21_matrix.h"
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabsl((A->matrix[i][j] - B->matrix[i][j])) > 1e-7) {
          res = FAILURE;
          break;
        }
      }
    }
  }
  return res;
}
