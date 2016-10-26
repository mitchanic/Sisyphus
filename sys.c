#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spiro.h"



point c_loc;
double c_ang;
double c_dist;


point baby_steps(point loc) {
/* Returns a point that is a step distance or less from the current point to
 * create smooth an seamless movement */
  point diff;
  diff.x = loc.x - c_loc.x;
  diff.y = loc.y - c_loc.y;
  double dist = sqrt((diff.x * diff.x) + (diff.y * diff.y));
  point ret;
  if(dist > 1.0) {
    double slope = diff.y / diff.x;
    double xsign = (diff.x >= 0 ? 1 : -1);
    double ysign = (diff.y < 0 ? 1 : -1);
    double ang = atan(slope);
    double xval = cos(ang);
    double yval = sin(ang);
    if((xsign > 0 && xval < 0) || (xsign < 0 && xval > 0)) {
      xval = (-1.0 * xval);
    }
    if((ysign > 0 && yval < 0) || (ysign < 0 && yval > 0)) {
      yval = (-1.0 * xval);
    }
    ret.x = xval;
    ret.y = yval;
  } else {
    ret = loc;
  }
  return ret;
}


void m_move(point loc) {
/* Moves tip to the specified location */

}


void home() {
/* Moves tip home (found via sensors) */

}

unsigned pline(char *line) {
  unsigned ret = 0;
  char *chek = malloc(15 * sizeof(char));
  for(int i=0; i<15; i++) {
    chek[[i] = line[i];
  }
  if(!strcmp(chek, "<polyline fill=") {
    ret = 1;
  }
  free(chek);
  return ret;
}


point point_from_line(char *line) {

}

void svg_read(char *fname) {
  char buf[514];
  char *inp;
  FILE *vecs;
  unsigned overflow;
  char *line;

  if((vecs = fopen(fname, "r"))) {
    while(!feof(vecs)) {
      overflow = 0;
      if((inp = fgets(buf, 514, vecs))) {
        line = strdup(inp);
        if(pline(line)) {
          printf("%s\n", line);
          point pt = point_from_line(line);

        if(strlen(line) == 513 && line[513] != '\n') {
          overflow = 1;

        } else {
          //
        }
        while(overflow == 1) {
          //
          if((inp = fgets(buf, 514, vecs))) {
            line = strdup(inp);
            if(strlen(line) == 513 && line[513] != '\n') {
              overflow = 1;
              //
            } else {
              //
              overflow = 0;
            }
          }
        }
      } else {
        exit(0);
      }
    }
    fclose(vecs);
    exit(0);
  }
}




int main() {
  /* Still need to write:
   * Convert SVG to point**
   * Convert point ** to SVG
   * Run Point** with offset
  */
  svg_read("Test2.svg");
  return 0;
}
