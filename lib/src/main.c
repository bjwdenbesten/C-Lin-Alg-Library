#include <stdio.h>
#include "linA.h"



int main() {
  matrix_T *a = NULL;
  FILE *fp = fopen("input.txt", "r");

  a = read_matrix(fp);

  print_lu(lu_decomposition(a));

  free_matrix(a);
  return 0;
}
