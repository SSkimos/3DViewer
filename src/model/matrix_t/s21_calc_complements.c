#include <math.h>

#include "s21_matrix.h"
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if ((!A) || (!result)) {
    return kError;
  } else if (((A->rows <= 0) || (A->columns <= 0))) {
    return kError;
  } else if (A->rows != A->columns) {
    return kCalculationError;
  } else if (s21_create_matrix(A->rows, A->columns, result) != 0) {
    return kError;
  }

  if (A->rows == 1) {
    result->matrix[0][0] = 1.0 * -1;
  } else {
    double tmpdeterm = 0.0;
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < A->rows; k++) {
        if (A->rows >= 2) {
          matrix_t tmp = {0};
          s21_crop(A, i, k, &tmp);
          s21_determinant(&tmp, &tmpdeterm);
          s21_remove_matrix(&tmp);
          result->matrix[i][k] = tmpdeterm * pow(-1, (i + k));
        }
      }
    }
  }
  return kOk;
}
