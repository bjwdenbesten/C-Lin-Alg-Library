<h1> CLinear: Linear Algebra implemented in C</h1>
<p> CLinear was created (for fun) as a library for C. </p>
<h2>Basic Instructions</h2>
<p>Testing can be done via src/main.c. Run <code>make</code> to compile and link the files with main.c. Run <code>make clean</code> to remove unwanted object files as well as the executable. A sample input is
provided in input.txt, as well as a sample program in main.c.</p>
<h2> Structure and Functions</h2>
<p> This library has two main structures: vectors and matrices. Vectors are represented with an int: length and a corresponding array of doubles. 
  A matrix has dimension specificity (rows and cols), as well as a corresponding vector structure representing its values in row-major order.</p>
  <h2> Functions </h2>
  <h4>General purpose Functions</h4>
  * <code>read_matrix(FILE *)</code>: Reads a matrix from a specified file in the following format <br \> <br \>
  rows, cols <br />
  a, b, c, d .. <br /> <br />
  Where a, b, c, d .. are the matrix's values in row-major order. <br /> <br />
  * <code>create_vector</code> and <code>create_matrix</code> both create each of their corresponding structures. <br \>
  * <code>create_identity_matrix</code> and <code>create_zero_matrix</code> create an identity and zero matrix respectively. <br \>
  * <code>print_matrix</code> and <code>print_vector</code> prints the contents of each respective structure to stdout. <br \>
  * <code>print_lu</code> prints the result of the LU decomposition of a specified matrix. <br \>
<h4> Matrix Operation Functions </h4>
* <code>matrix_add</code> computes the sum of two matrices. <br \>
* <code>matrix_mult_c</code> computes the product of a matrix and a constant. <br \>
* <code>matrix_mult</code> computes the product of two matrices. <br \>
* <code>transpose</code> computes the transpose of a matrix. <br \>
* <code>row_reduce</code> row reduces a given matrix. Returns a structure reduction_T, containing info about the row reduction. <br \>
* <code>determinant</code> computes the determinant of a given matrix. <br \>
* <code>lu_decomposition</code> computes the LU(P) decomposition of a given matrix. <br \>
<h4>Important</h4>
Users must call <code>free_matrix</code> or <code>free_vector</code> when finished using a matrix or vector to avoid memory leaks.
