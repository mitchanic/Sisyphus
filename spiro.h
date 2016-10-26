#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct color {
  int r;
  int g;
  int b;
} color;

typedef struct point {
  double x;
  double y;
} point;

typedef struct circ {
  double rad;
  double ang;
  double barlen;
  double radperstep;
} circ;

color white = {255, 255, 255};
color black = {0, 0, 0};
color blue = {0, 0, 255};
color red = {255, 0, 0};
color green = {0, 255, 0};
double pi = 3.14159265358979323846264338;




color** blank(unsigned widh);
/* Creates a 2D array of colors, where each color is blank (white) */


void border(color **pix, unsigned widh);
/* Fills in given array of colors to form a circular "border" of diameter widh */


void ppmmaker(color **pix, unsigned widh);
/* Generates a PPM from the given 2D array of colors and widh (width and height) */


point barcirc(circ *c);
/* Returns the point from the next itteration of a circle's movement specs,
   and updates the circle's current position */


void run(color **pix, int widh, circ *b1, circ *b2, circ *b3, int steps);
/* Generates a PPM from a 2D color array, three input circle structs and the
   number of time steps */
