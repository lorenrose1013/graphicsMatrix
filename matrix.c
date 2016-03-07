#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int i, j;
  for (i = 0; i < m->rows; i++){
    for (j = 0; j < m->lastcol; j++){
      printf("%f ", m->m[i][j]); //i know it takes doubles but this is so much nicer
    }
    printf("\n");
  }
}


/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i, j;
  m->lastcol = m->rows;
  for (i = 0; i < m->rows; i++){
    for (j = 0; j < m->lastcol; j++){
      if (i == j){
        m->m[i][j] = 1;
      }
      else{
        m->m[i][j] = 0;
      }
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
	int i, j;
	for (i = 0; i < m->rows; i++){
		for (j = 0; j < m->lastcol; j++){
		m->m[i][j] = m->m[i][j] * x;
		}
	}
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
	if (a->rows != b->lastcol){
		//cant multiply
		return;
	}
	//it works now!!!
	struct matrix *result;
	result = new_matrix(a->rows, b->lastcol);
	result->lastcol = b->lastcol;

	int r, c, mid;
	for(r = 0; r < a->rows; r++){
	  for(c = 0; c < b->lastcol; c++){
	    int sum = 0;
	    for (mid = 0; mid < a->lastcol; mid++){
	      sum += a->m[r][mid] * b->m[mid][c];
	    }
	    result->m[r][c] = sum;
	  }
	}

	copy_matrix(result, b);
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
	struct matrix *trans_mat;
	trans_mat = new_matrix(4,4);
	ident(trans_mat);
	trans_mat->m[0][3] = x;
	trans_mat->m[1][3] = y;
	trans_mat->m[2][3] = z;
	return trans_mat;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix *scale; 
  scale = new_matrix(4,4); //initialize the matrix
  ident(scale);
  scale->m[0][0] = x;
  scale->m[1][1] = y;
  scale->m[2][2] = z;
  return scale;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  struct matrix *rotX_mat; 
  rotX_mat = new_matrix(4,4); //initialize the matrix
  ident(rotX_mat);

  double rad = theta * M_PI / 180;
  rotX_mat->m[1][1] = cos(rad);
  rotX_mat->m[1][2] = - sin(rad);
  rotX_mat->m[2][1] = sin(rad);
  rotX_mat->m[2][2] = cos(rad);
  
  return rotX_mat;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  struct matrix *rotY_mat; 
  rotY_mat = new_matrix(4,4); //initialize the matrix
  ident(rotY_mat);

  double rad = theta * M_PI / 180;
  rotY_mat->m[0][0] = cos(rad);
  rotY_mat->m[0][2] = - sin(rad);
  rotY_mat->m[2][0] = sin(rad);
  rotY_mat->m[2][2] = cos(rad);
  
  return rotY_mat;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  struct matrix *rotZ_mat; 
  rotZ_mat = new_matrix(4,4); //initialize the matrix
  ident(rotZ_mat);

  double rad = theta * M_PI / 180;
  rotZ_mat->m[0][0] = cos(rad);
  rotZ_mat->m[0][1] = - sin(rad);
  rotZ_mat->m[1][0] = sin(rad);
  rotZ_mat->m[1][1] = cos(rad);
  
  return rotZ_mat;
}
