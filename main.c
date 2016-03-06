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
  struct matrix *identity_matrix;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  identity_matrix = new_matrix(4, 4);
  print_matrix(identity_matrix);
  ident(identity_matrix);
  print_matrix(identity_matrix);
  scalar_mult(5, identity_matrix);
  print_matrix(identity_matrix);

  struct matrix *test_mat = make_rotX(1);
  print_matrix(test_mat);

  free_matrix( transform );
  free_matrix( edges );
}  
