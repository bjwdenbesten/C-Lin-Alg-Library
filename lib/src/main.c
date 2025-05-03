#include <stdio.h>
#include "linA.h"



int main() {
  matrix_T *a = NULL;
  FILE *fp = fopen("input.txt", "r");

  // reads the matrix from the file
  a = read_matrix(fp);
  //prints the matrix to stdout
  print_matrix(a);
  //get the lu decomposition of a:
  lu_decomposition_T *info = lu_decomposition(a);
  //print the lu decomp info
  print_lu(info);

  //read matrix b and c from the file
  matrix_T *b = read_matrix(fp);
  matrix_T *c = read_matrix(fp);

  print_matrix(b);
  print_matrix(c);

  //multiply b and c, print the result
  matrix_T *d = matrix_mult(b, c);
  print_matrix(d);
  
  //make sure to free matrices at the end of the program
  free_matrix(a);
  free_matrix(b);
  free_matrix(c);
  //this includes the matrices in the lu decomposition struct
  free_matrix(info->upper);
  free_matrix(info->lower);
  free_matrix(info->P);
  return 0;
}
