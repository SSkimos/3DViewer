#include "s21_affin_p.h"
#include "s21_data_structure.h"
#include <stdio.h>


int Scale(data_t **A, double zoom) {
  int ret = 0;
  if ((int) zoom != 0) {
    ret = 1;
  } else {
    ret = 1;
  }
  return ret;
}

int Move(data_t **A, double a, int cord) {
  int f = 0;
	for (int i = 0; i < (*A)->vertices_count / 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j % cord == 0) {
        (*A)->vertex_array[f] += a;
        printf("%f FLOATER\n ", (*A)->vertex_array[f]);
        f++;
      }
    }
  }
  return 0;
}

int MoveX(data_t **A, double a) {
  return Move(A, a, kX);
}

int MoveY(data_t **A, double a) {
  return Move(A, a, kY);
}

int MoveZ(data_t **A, double a) {
  return Move(A, a, kZ);
}

void RotationX(data_t *A, double angle) {
	/* for (int i = 0; i < A->rows; i++) {
		double temp_y = A->data[i][1];
		double temp_z = A->data[i][2];
		A->data[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
		A->data[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
	} */
}
