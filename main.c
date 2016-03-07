#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  struct matrix *tmp1;
  struct matrix *tmp2;

  tmp1 = new_matrix(2,3);
  tmp2 = new_matrix(3,2);

  tmp1->lastcol = 3;
  tmp2->lastcol = 2;

  tmp1->m[0][0] = 1;
  tmp1->m[0][1] = 2;
  tmp1->m[0][2] = 3;
  tmp1->m[1][0] = 4;
  tmp1->m[1][1] = 5;
  tmp1->m[1][2] = 6;

  tmp2->m[0][0] = 7;
  tmp2->m[0][1] = 8;
  tmp2->m[1][0] = 9;
  tmp2->m[1][1] = 10;
  tmp2->m[2][0] = 11;
  tmp2->m[2][1] = 12;


  print_matrix(tmp1);
  print_matrix(tmp2);

  matrix_mult(tmp1, tmp2);

  print_matrix(tmp2);
  

  free_matrix( transform );
  free_matrix( edges );
}  
