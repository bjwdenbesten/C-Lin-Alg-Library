#include <stdio.h>
#include "linA.h"



int main() {
  matrix_T *a = NULL;
  matrix_T *b = NULL;

  double val[9] = {3, 1, 6, -6, 0, -16, 0, 8, -17};
  vector_T *vec = create_vector(9, val);
  a = create_matrix(3, 3, vec);
  double det = determinant(a);
  printf("Determinant: :%lf\n", det);

  free_matrix(a);
  return 0;
}
