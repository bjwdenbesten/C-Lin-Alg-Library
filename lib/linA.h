#include <stdio.h>
#include <stdbool.h>

#ifndef linA_H__
#define linA_H__

typedef struct {
  int size;
  double *nums;
} vector_T;

typedef struct {
  int rows;
  int cols;
  vector_T *vals;
} matrix_T;

typedef struct {
  matrix_T *matrix;
  int sign;
  bool swapped;
  int num_ks;
  double *ks;
} reduction_T;

typedef struct {
  matrix_T *upper;
  matrix_T *lower;
} lu_decomposition_T;


/* basic function declarations */
vector_T *create_vector(int, double *);
matrix_T *create_matrix(int, int, vector_T *);
matrix_T *read_matrix(FILE *);
matrix_T *create_identity_matrix(int);
matrix_T *create_zero_matrix(int, int);
void free_matrix(matrix_T *);
void print_matrix(matrix_T *);
void free_vector(vector_T *);
void print_vector(vector_T *);

/* matrix operation function declarations */
matrix_T *matrix_add(matrix_T *, matrix_T *);
matrix_T *matrix_mult_c(matrix_T *, int);
matrix_T *matrix_mult(matrix_T *, matrix_T *);
matrix_T *transpose(matrix_T *);
reduction_T *row_reduce(matrix_T *);
double determinant(matrix_T *);
lu_decomposition_T *lu_decomposition(matrix_T *);
void print_lu(lu_decomposition_T *);


/* vector operation functions */
vector_T *vector_add(vector_T *, vector_T *);
vector_T *vector_mult_c(vector_T *, double);
double magnitude(vector_T *);




#endif  // linA_H__
