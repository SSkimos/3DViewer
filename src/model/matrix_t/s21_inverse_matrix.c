#include <math.h>

#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if ((!A) || (!result)) {
    return kError;
  } else if (((A->rows <= 0) || (A->columns <= 0))) {
    return kError;
  } else if (A->rows != A->columns) {
    return kCalculationError;
  }
  // if (A->rows == 1) {
  //   if (fabs(A->matrix[0][0]) < 1e-6) {
  //     return kCalculationError;
  //   }
  //   s21_create_matrix(1, 1, result);
  //   result->matrix[0][0] = 1 / A->matrix[0][0];
  // } else {
  //   err = s21_determinant(A, &determ);
  //   if (fabs(determ) < 1e-6) {
  //     return kCalculationError;
  //   }
  //   if (!err) {
  //     err = s21_calc_complements(A, &tmp);
  //   }
  //   if (!err) {
  //     err = s21_mult_number(&tmp, 1.0 / determ, &tmp1);
  //   }
  //   if (!err) {
  //     err = s21_transpose(&tmp1, result);
  //   }
  //   s21_remove_matrix(&tmp);
  //   s21_remove_matrix(&tmp1);
  // }
  return 0;
}
