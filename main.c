#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;

  clear_screen(s);
  c.red = 255;
  c.green = 0;
  c.blue = 0;

  struct matrix *edges;
  struct matrix *transform;


  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  add_point(edges, 225, 225, 0);
  add_point(edges, 275, 225, 0);
  add_point(edges, 275, 275, 0);
  add_point(edges, 225, 275, 0);
  add_point(edges, 225, 225, 0);

  print_matrix(edges);
  printf("edges last col: %d\n", edges->lastcol);
  draw_lines(edges, s, c);

  display(s);

  free_matrix( transform );
  free_matrix( edges );
}  
