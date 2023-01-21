#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (!result) {
    return kError;
  } else if ((rows <= 0) || (columns <= 0)) {
    result->rows = rows;
    result->columns = columns;
    return kError;
  } else {
    result->matrix = calloc(rows, sizeof(long double *));
    if (!result->matrix) {
      return kError;
    }
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(long double));
    if (!result->matrix[i]) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      return kError;
    }
  }
  result->rows = rows;
  result->columns = columns;
  return kOk;
}
