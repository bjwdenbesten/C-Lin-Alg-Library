#include "linA.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* creates a new vector object */

vector_T *create_vector(int size, double *nums) {
  if (size < 0) {
    fprintf(stderr, "Error in create_vector\n");
    return NULL;
  }

  vector_T *new = malloc(sizeof(vector_T));
  assert(new != NULL);

  new->size = size;
  new->nums = malloc(sizeof(double) * size);
  assert(new->nums != NULL);

  if (nums != NULL) {
    for (int i = 0; i < size; i++) {
      new->nums[i] = nums[i];
    }
  }
  return new;
}

/* creates a new matrix object */

matrix_T *create_matrix(int rows, int cols, vector_T *vec) {
  if (rows <= 0 || cols  <= 0) {
    fprintf(stderr, "Invalid dimensions in create_matrix\n");
    return NULL;
  }

  matrix_T *new = malloc(sizeof(matrix_T));
  assert(new != NULL);

  new->rows = rows;
  new->cols = cols;
  new->vals = vec;
  return new;
}

matrix_T *read_matrix(FILE *fp) {
  assert(fp != NULL);
  
  int row = 0;
  int col = 0;

  fscanf(fp, "%d,%d\n", &row, &col);

  double *vals = malloc(sizeof(double) * row * col);

  for (int i = 0; i < row * col; i++) {
    fscanf(fp, "%lf", &vals[i]);
    if (i == row * col - 1) {
      fscanf(fp, "\n");
    }
    else {
      fscanf(fp, ",");
    }
  }
  vector_T *vec = create_vector(row * col, vals);
  matrix_T *matrix = create_matrix(row, col, vec);
  return matrix;
}



matrix_T *create_identity_matrix(int size) {
  if (size <= 0) {
    fprintf(stderr, "Invalid dimensions in create_identity_matrix\n");
    return NULL;
  }

  matrix_T *new = malloc(sizeof(matrix_T));
  assert(new != NULL);

  new->rows = size;
  new->cols = size;

  double *i_v = malloc(sizeof(double) * size * size);
  assert(i_v != NULL);

  for (int i = 0; i < size * size; i++) {
    if (i % (size + 1) == 0) {
      i_v[i] = 1;
    }
    else {
      i_v[i] = 0;
    }
  }

  vector_T *vec = create_vector(size * size, i_v);

  new->vals = vec;
  free(i_v);
  return new;
}


matrix_T *create_zero_matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    fprintf(stderr, "Invalid dimensions in create_zero_matrix\n");
    return NULL;
  }

  matrix_T *new = malloc(sizeof(matrix_T));
  assert(new != NULL);
  new->rows = rows;
  new->cols = cols;

  double *val = malloc(sizeof(double) * rows * cols);
  for (int i = 0; i < rows * cols; i++) {
    val[i] = 0;
  }

  vector_T *vec = create_vector(rows * cols, val);
  new->vals = vec;
  return new;
}


/* frees a matrix object and its data */
void free_matrix(matrix_T *m) {
  assert(m != NULL);
  free(m->vals->nums);
  free(m->vals);
  free(m);
}


/* prints matrix to stdout */
void print_matrix(matrix_T *m) {
  assert(m != NULL);
  printf("Matrix: %d x %d:\n", m->rows, m->cols);
  vector_T *ov = m->vals;

  for (int i = 1; i <= ov->size; i++) {
    printf("%.5f ", ov->nums[i-1]);
    if (i % m->cols == 0) {
      printf("\n");
    }
  }
  printf("\n");
}


/* frees a vector */
void free_vector(vector_T *v) {
  free(v->nums);
  free(v);
}


/* prints a vector to stdout */
void print_vector(vector_T *v) {
  assert(v != NULL);
  printf("Vector of size: %d\n", v->size);
  for (int i = 0; i < v->size; i++) {
    printf("%.5f\n", v->nums[i]);
  }
  printf("\n");
}



matrix_T *matrix_add(matrix_T *a, matrix_T *b) {
  assert(a != NULL && b != NULL);

  if (a->cols != b->cols || a->rows != b->rows) {
    fprintf(stderr, "Incorrect dimensions in matrix_add\n");
    return NULL;
  }

  int size = a->vals->size;
  double *val = malloc(sizeof(double) * size);

  for (int i = 0; i < size; i++) {
    val[i] = a->vals->nums[i] + b->vals->nums[i];
  }


  vector_T *n = create_vector(size, val);
  matrix_T *new = create_matrix(a->rows, a->cols, n);
  return new;
}

matrix_T *matrix_mult_c(matrix_T *a, int c) {
  assert(a != NULL);

  int size = a->vals->size;
  double *val = malloc(sizeof(double) * size);

  for (int i = 0; i < size; i++) {
    val[i] = c * a->vals->nums[i];
  }

  vector_T *n = create_vector(size, val);
  matrix_T *new = create_matrix(a->rows, a->cols, n);
  return new;
}


matrix_T *matrix_mult(matrix_T *a, matrix_T *b) {
  assert(a != NULL && b != NULL);

  if (a->cols != b->rows) {
    fprintf(stderr, "Invalid dimensions in matrix_mult\n");
    return NULL;
  }

  if (a->vals == NULL || b->vals == NULL) {
    fprintf(stderr, "NULL vector in matrix_mult\n");
    return NULL;
  }
  
  double *res = malloc(sizeof(double) * a->rows * b->cols);

  for (int i = 0; i < a->rows * b->cols; i++) {
    res[i] = 0;
  }

  vector_T *vec_a = a->vals;
  vector_T *vec_b = b->vals;

  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < b->cols; j++) {
      int start_index_row = i * a->cols;
      
      //do the operation
      for (int k = 0; k < a->cols; k++) {
        res[start_index_row + j] += (vec_a->nums[start_index_row + k]) * (vec_b->nums[j + b->cols * k]);
      }
    }
  }

  vector_T *result = create_vector(a->rows * b->cols, res);
  matrix_T *new = create_matrix(a->rows, b->cols, result);
  return new;
}

matrix_T *transpose(matrix_T *a) {
  assert(a != NULL);

  if (a->vals == NULL) {
    fprintf(stderr, "NULL vector in transpose\n");
    return NULL;
  }

  double *vals= malloc(sizeof(double) * a->vals->size);

  int starting_index = 0;
  int curr_index = 0;

  for (int i = 0; i < a->vals->size; i++) {
    vals[curr_index] = a->vals->nums[i];
    curr_index += a->rows;

    if ((i+1) % a->cols == 0) {
      starting_index++;
      curr_index = starting_index;
    }

  }

  vector_T *vec = create_vector(a->vals->size, vals);

  matrix_T *new = create_matrix(a->cols, a->rows, vec);
  return new;
}



reduction_T *row_reduce(matrix_T *a) {
  assert(a != NULL);

  int sign = 1;
  bool is_swapped = false;

  reduction_T *reduction_info = malloc(sizeof(reduction_T));
  int num_ks = 0;

  for (int i = a->rows - 1; i > 0; i--) {
    num_ks += i;
  }

  reduction_info->ks = malloc(sizeof(double) * num_ks);
  int index_k = 0;


  /* create an array of pointers to hold all the row vectors */
  vector_T **rows = malloc(sizeof(vector_T *) * a->rows);

  for (int i = 0; i < a->rows; i++) {
    /* array of doubles to hold each row's value */

    double *row = malloc(sizeof(double) * a->cols);

    int offset = i * a->cols;
    int index = 0;
    for (int j = offset; j < a->cols + a->cols * i; j++) {
      row[index] = a->vals->nums[j];
      index++;
    }
    vector_T *vec = create_vector(a->cols, row);
    rows[i] = vec;
  }

  /* now we have an array of pointers representing rows;
   * start row reduction */

  int num_pivots = 0;

  for (int i = 0; i < a->cols; i++) {
    /* check if already in form */

    bool zeros = true;
    int index = -1;

    for (int j = num_pivots + 1; j < a->rows; j++) {
      if (rows[j]->nums[i] != 0) {
        zeros = false;
        index = j;
        break;
      }
    }
    
    /* if the ith col is in form, we go to the next col */
    if (zeros) {
      if (num_pivots < a->rows && rows[num_pivots]->nums[i] != 0) {
        num_pivots++;
      }
      continue;
    }

    /* make sure col doesn't start with a zero */
    if (rows[num_pivots]->nums[i] == 0) {
      /* swaps the row with a non-zero value */
      vector_T *temp = rows[num_pivots];
      rows[num_pivots] = rows[index];
      rows[index] = temp;
      sign *= -1;
      is_swapped = true;
    }

    /* now we can just row reduce below the pivot */

    vector_T *free_ptr = NULL;

    for (int j = num_pivots + 1; j < a->rows; j++) {
      double coeff = rows[num_pivots]->nums[i];
      if (rows[j]->nums[i] != 0) {
        double scale = rows[j]->nums[i] / coeff;
        reduction_info->ks[index_k] = scale;
        index_k++;

        vector_T *copy = NULL;
        double *copy_vals = malloc(sizeof(double) * a->cols);
        for (int i = 0; i < a->cols; i++) {
          copy_vals[i] = rows[num_pivots]->nums[i];
        }
        copy = create_vector(a->cols, copy_vals);
        free_ptr = copy;
        copy = vector_mult_c(copy, scale);
        free_vector(free_ptr);
        free_ptr = copy;
        copy = vector_mult_c(copy, -1);
        free_vector(free_ptr);
        rows[j] = vector_add(rows[j], copy);
        free_vector(copy);
      }
      else {
        reduction_info->ks[index_k] = 0;
        index_k++;
      }
    }
    num_pivots++;
  }

  /* now transform the array of vectors back into a matrix */
  vector_T *final_vec = NULL;

  double *final_vals = malloc(sizeof(double) * a->vals->size);

  int o_index = 0;

  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < a->cols; j++) {
      final_vals[o_index] = rows[i]->nums[j];
      o_index++;
     }
   }

  final_vec = create_vector(a->vals->size, final_vals);
  matrix_T *new_matrix = create_matrix(a->rows, a->cols, final_vec);

  for (int i = 0; i < a->rows; i++) {
    free_vector(rows[i]);
  }

  reduction_info->matrix = new_matrix;
  reduction_info->sign = sign;
  reduction_info->num_ks = index_k;
  reduction_info->swapped = is_swapped;

  return reduction_info;
}

double determinant(matrix_T *a) {
  assert(a != NULL);
  if (a->cols != a->rows) {
    fprintf(stderr, "Cannot perform determinant on non square matrix\n");
    return 0;
  }
  reduction_T *info = row_reduce(a);
  matrix_T *rrm = info->matrix;
  print_matrix(rrm);
  double det = 1;
  int index = 0;
  for (int i = 0; i < a->rows; i++) {
    index = i + i * a->cols;
    det *= rrm->vals->nums[index];
  }
  int sign = info->sign;
  free(info->matrix);
  free(info->ks);
  free(info);
  return det * sign;
}

lu_decomposition_T *lu_decomposition(matrix_T *a) {
  assert(a != NULL);

  reduction_T *red_info = row_reduce(a);

  if (red_info->swapped) {
    fprintf(stderr, "A pure LU decomposition doesn't exist\n");
    return NULL;
  }

  lu_decomposition_T *sol = malloc(sizeof(lu_decomposition_T));
  sol->upper = red_info->matrix;
  
  double *vals = calloc(1, a->rows * a->rows * sizeof(double));

  /* insert ones on diagnal */

  for (int i = 0; i < a->rows; i++) {
    int index = i + i * a->rows;
    vals[index] = 1;
  }

  /* insert k values below */
  int k_index = 0;

  for (int i = 0; i < a->rows; i++) {
    for (int j = i + 1; j < a->rows; j++) {
      int row_index = j * a->rows;
      vals[row_index + i] = red_info->ks[k_index];
      k_index++;
    }
  }
  vector_T *vec = create_vector(a->rows * a->rows, vals);
  matrix_T *lower = create_matrix(a->rows, a->rows, vec);
  sol->lower = lower;
  free(red_info->ks);
  free(red_info);
  return sol;
}

void print_lu(lu_decomposition_T *a) {
  assert(a != NULL);
  printf("Lower:\n");
  print_matrix(a->lower);
  printf("Upper:\n");
  print_matrix(a->upper);
}




/* basic vector functions below */

vector_T *vector_add(vector_T *a, vector_T *b) {
  assert(a != NULL & b != NULL);
  if (a->size != b->size) {
    fprintf(stderr, "Vectors not of the same size in vector_add!\n");
    return NULL;
  }

  double *vals = malloc(sizeof(double) * a->size);

  for (int i = 0; i < a->size; i++) {
    vals[i] = a->nums[i] + b->nums[i];
  }

  vector_T *new_vec = create_vector(a->size, vals);
  return new_vec;
}


vector_T *vector_mult_c(vector_T *a, double c) {
  assert(a != NULL);
  
  double *vals = malloc(sizeof(double) * a->size);

  for (int i = 0; i < a->size; i++) {
    vals[i] = c * a->nums[i];
  }

  vector_T *new_vec = create_vector(a->size, vals);
  return new_vec;
}


double magnitude(vector_T *a) {
  assert(a != NULL);
  int sum = 0;
  for (int i = 0; i < a->size; i++) {
    sum += a->nums[i] * a->nums[i];
  }
  return sqrt(sum);
}







