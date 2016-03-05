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
//  struct matrix *identity_matrix;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

 //identity_matrix = new_matrix(4, 4);
  // print_matrix(identity_matrix);
  // ident(identity_matrix);
  // print_matrix(identity_matrix);
  
  free_matrix( transform );
  free_matrix( edges );
}  
