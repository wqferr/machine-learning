#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix matrix;


#include "linalg/linalg.h"
#include "linalg/vector.h"

/* Operation was not successful due to one or more of
 * the operands' dimensions */
#define LAMAT_INCOMPATIBLE_DIM 1

/* Operation was not successful due to one of the coordinates
 * being outside the bounds of a matrix. */
#define LAMAT_OOB 2


/* Creates a new matrix whose elements are in data,
 * ordered by rows.
 * If data is NULL, the new matrix's elements are undefined. */
int mat_new(matrix **m, const LINALG_SCALAR *data, int rows, int cols);

/* Allocates a matrix in an invalid state.
 * Matrices created by this function can be used for function output. */
int mat_alloc(matrix **m);

/* Creates an identity matrix of the given order. */
int mat_identity(matrix **m, int order);

/* Creates a null matrix with the given dimensions. */
int mat_zero(matrix **m, int rows, int cols);

/* Creates a new matrix with same values as src. */
int mat_dup(matrix **dst, const matrix *src);

/* Copies src's values and dimensions into dst. */
int mat_cpy(matrix *dst, const matrix *src);

/* Frees resources allocated for m */
int mat_del(matrix *m);


/* Writes to *rows and *cols the dimensions of m.
 * If any of the int pointers are NULL, it is left untouched. */
int mat_dim(const matrix *m, int *rows, int *cols);

/* Copies m's elements into data. */
int mat_get_data(const matrix *m, LINALG_SCALAR *data);

/* Copies data's elements into m. */
int mat_set_data(matrix *m, const LINALG_SCALAR *data);


/* Writes the element with corresponding position into out.
 * Possible errors:
 *  - LAMAT_OOB */
int mat_read(const matrix *m, int row, int col, LINALG_SCALAR *out);

/* Alternative version of mat_read for easier handling.
 * Returns the element with corresponding position in the matrix.
 * No error or boundary checks are made. Useful for quick acces to values.
 */
LINALG_SCALAR mat_get(const matrix *m, int row, int col);

/* Writes r into the matrix's corresponding position.
 * Possible errors:
 *  - LAMAT_OOB */
int mat_write(matrix *m, int row, int col, LINALG_SCALAR r);

/* Unsafe version of mat_write.
 * Writes r into the matrix's corresponding position.
 * No error checks are made. */
void mat_set(matrix *m, int row, int col, LINALG_SCALAR r);


/* Writes the result of a + b into out.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_add(const matrix *a, const matrix *b, matrix *out);

/* Writes the result of a + b into a.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_add_(matrix *a, const matrix *b);

/* Writes the result of a - b into out.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_sub(const matrix *a, const matrix *b, matrix *out);

/* Writes the result of a - b into a.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_sub_(matrix *a, const matrix *b);

/* Writes the result of a * b into out.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_mul(const matrix *a, const matrix *b, matrix *out);

/* Writes the result of a * b into a.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_mul_(matrix *a, const matrix *b);

/* Element-wise multiplication of v with every row of m.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_rmul(const matrix *m, const vector *v, matrix *out);

/* Element-wise in place multiplication of v with every row of m.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_rmul_(matrix *m, const vector *v);

/* Element-wise multiplication of v with every column of m.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_cmul(const matrix *m, const vector *v, matrix *out);

/* Element-wise in place multiplication of v with every column of m.
 * Possible errors:
 *  - LAMAT_INCOMPATIBLE_DIM */
int mat_cmul_(matrix *m, const vector *v);

/* Writes the result of s * m into out. */
int mat_smul(const matrix *m, LINALG_SCALAR s, matrix *out);

/* Writes the result of s * m into m. */
int mat_smul_(matrix *m, LINALG_SCALAR s);

/* Writes the result of (1/s) * m into out. */
int mat_sdiv(const matrix *m, LINALG_SCALAR s, matrix *out);

/* Writes the result of (1/s) * m into m. */
int mat_sdiv_(matrix *m, LINALG_SCALAR s);


/* Transposes m. */
int mat_transpose_(matrix *m);

#endif
