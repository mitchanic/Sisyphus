#include "spiro.h"

color** blank(unsigned widh) {
  /* Creates a 2D array of colors, where each color is blank (white) */
  color** rows = malloc(widh * sizeof(color*));
  for(int i=0; i<widh; i++) {
    color* col = malloc(widh * sizeof(color));
    for(int j=0; j<widh; j++) {
      //color white = {255, 255, 255};
      col[j] = white;
    }
    rows[i] = col;
  }
  return rows;
}

void border(color **pix, unsigned widh) {
  /* Fills in given array of colors to form a circular "border" of diameter widh */
  double rad = ( (double) widh) / 2.0;
  point cent;
  cent.x = (double) widh / 2.0;
  cent.y = (double) widh / 2.0;
  for(int i=0; i<(widh/2); i++) {
    double xdist = cent.x - (double) i;
    double ang = acos(xdist / rad);
    int yval = round((sin(ang) * rad) + cent.y);
    color *col = pix[i];
    col[yval - 1] = black;
    col[widh - yval] = black;

    col = pix[widh - i - 1];
    col[yval - 1] = black;
    col[widh - yval] = black;

    col = pix[widh - yval];
    col[i] = black;
    col[widh - i - 1] = black;

    col = pix[yval - 1];
    col[i] = black;
    col[widh - i - 1] = black;
  }
}


void ppmmaker(color **pix, unsigned widh) {
  /* Generates a PPM from the given 2D array of colors and widh (width and height) */
  FILE *new = fopen("pic.ppm", "w");
  if(new) {
    fprintf(new, "P3\n%d\t%d\n255\n", widh, widh);
    for(int i=0; i<widh; i++) {
      for(int j=0; j<widh; j++) {
        color *col = pix[j];
        color c = col[i];
        fprintf(new, "%d\t%d\t%d\n", c.r, c.g, c.b);
      }
    }
  }
  fclose(new);
}

point barcirc(circ *c) {
  /* Returns the point from the next itteration of a circle's movement specs,
     and updates the circle's current position */
  point ret;
  ret.x = c->barlen * cos(c->ang);
  ret.y = c->barlen * sin(c->ang);
  double nang = c->ang + c->radperstep;
  c->ang = nang;
  return ret;
}

void run(color **pix, int widh, circ *b1, circ *b2, circ *b3, int steps) {
  /* Generates a PPM from a 2D color array, three input circle structs and the
     number of time steps */
  int rad = (int) round((widh - 1) / 2);
  double max = b1->barlen + b2->barlen + b3->barlen;
  if(max < rad) {
    point cent = {rad, rad};
    point p1, p2, p3;
    color *cols;
    for(int i=0; i<steps; i++) {
      p1 = barcirc(b1);
      p1.x += cent.x;
      p1.y += cent.y;

      p2 = barcirc(b2);
      p2.x += p1.x;
      p2.y += p1.y;

      p3 = barcirc(b3);
      p3.x += p2.x;
      p3.y += p2.y;

      cols = pix[(int) round(p1.x)];
      cols[(int) round(p1.y)] = green;
      cols = pix[(int) round(p2.x)];
      cols[(int) round(p2.y)] = red;
      cols = pix[(int) round(p3.x)];
      cols[(int) round(p3.y)] = blue;
    }
  } else {
    printf("Pen will be out of bounds\n");
  }
}



int main(int argc, char* argv[]) {
  int widh = 2001;
  int rad = (int) round((widh - 1) / 2);
  color** bl = blank(widh);
  border(bl, widh);
  circ *c1 = malloc(sizeof(circ));
  c1->barlen = 600;
  c1->ang = pi/2.0;
  c1->radperstep = ((2.0 * pi) / 1000000.0);

  circ *c2 = malloc(sizeof(circ));
  c2->barlen = 50;
  c2->ang = pi/2.0;
  c2->radperstep = (2.0 * pi) / 5000.0;

  circ *c3 = malloc(sizeof(circ));
  c3->ang = pi/2.0;
  c3->barlen = 200;
  c3->radperstep = (2.0 * pi) / 1000.0;
  printf("go\n");

  run(bl, widh, c1, c2, c3, 1000000);
  printf("went\n");
  ppmmaker(bl, widh);
  return 0;
}
