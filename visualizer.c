#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct color {
  int r;
  int g;
  int b;
} color;

typedef struct point {
  float x;
  float y;
} point;

float pi = 3.14159265358079323846264338;

color **blank(int widh) {
  color **pixels = malloc(widh * sizeof(color *));
  for(int i=0; i<widh; i++) {
    color *col = malloc(widh * sizeof(color));
    color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    for(int j=0; j<widh; j++) {
      col[j] = white;
    }
    pixels[i] = col;
  }
  return pixels;
}

void circle(color **pix, int widh) {
  int rad = (widh - 1)/2;
  int x;
  int y;
  int x2;
  int y2;
  color black = {0, 0, 0};
  for(int i=0; i<rad; i++) {
    x = i;
    //x2 = 101-i;
    y = (int) round(sqrt((rad * rad) - ((rad - x) * (rad - x)))) + rad;
    //y2 = 101 - y;
    color *col = pix[x];
    col[y] = black;
    col[(widh - 1) - y] = black;
    col = pix[(widh - 1) - x];
    col[y] = black;
    col[(widh - 1) - y] = black;
        //pix[x][y] = black;
    //pix[x][y2] = black;
    ///pix[x2][y] = black;
    //pix[x2][y2] = black;
    //printf("%d\t%d\n", x, y);
  }
}
/*
int func(int a) {
  FILE *new = fopen("pic.ppm", "w");
  if(new) {
    fprintf(new, "P3\n100 100\n255\n");
*/

void print_pix(color **pix, int widh) {
  unsigned black = 0;
  for(int i=0; i<widh; i++) {
    color *col = pix[i];
    for(int j=0; j<widh; j++) {
      color c = col[j];
      printf("%d\t%d\t%d\n", c.r, c.g, c.b);//"%d\n", (100 * i) + j);
      if(c.r == 0) {
        ++black;
      }
    }
  }
  //printf("Black: %d\n", black);
}

void spiro(float orad, float irad, float poff, float revs, color **pix, int widh) {
  if(irad >= orad || poff > irad || widh < orad || orad < 0 || irad < 0 || poff < 0 || widh < 0) {
    return;
  }
  float pang = 0;
  float iang = 0;
  for(int i=0; i<(revs * 360); i++) {
    point icent;
    icent.x = ((orad - irad) * cos(iang)) + orad;
    icent.y = ((orad - irad) * sin(iang)) + orad;

    point pcent;
    pcent.x = poff * cos(pang);
    pcent.y = poff * sin(pang);

    point ret;
    ret.x = icent.x + pcent.x;
    ret.y = icent.y + pcent.y;

    color bb = {0, 0, 255};
    int xx = (int) round(ret.x);
    int yy = (int) round(ret.y);
    color *col = pix[xx];
    col[yy] = bb;

    pang += (2 * pi)/360.0;
    iang += ((((2 * pi) / 360.0) * irad) / ((2 * pi) * orad)) * (2 * pi);
  }
}

color next_color(color in) {
  color c = in;
  if(c.g == 255) {
    if(c.b == 255) {
      --c.g;
    } else {
      ++c.b;
    }
  } else {
    if(c.b == 255) {
      if(c.g == 0) {
        --c.b;
      } else {
        --c.g;
      }
    } else {
      if(c.b == 0) {
        ++c.g;
      } else {
        --c.b;
      }
    }
  }

  return c;
}


void put_in_ppm(color c, unsigned x, unsigned y, color **pix, unsigned rad) {
  if(x > (2 * rad) + 1) {
    x = (2 * rad) + 1;
  }
  if(y > (2 * rad) + 1) {
    y = (2 * rad) + 1;
  }
  color *col = pix[x];
  col[y] = c;
}


float aeq(unsigned t, float curr, unsigned style) {
  float base = (2 * pi);
  if(style == 0) {
    return base * (float) ((float) t / 1000);
  }
  return base * (float) ((float) t / 1000);
}

float pat(float ang, float a, float b, float c, float d, float e) {
  return a * sin((b * (ang + c)) + d) + e;
}


float req(unsigned t, float acurr, float rcurr, unsigned style) {
  if(style == 0) {
    return 0.5;//sin(acurr);
  }
  if(style == 1) {
    return sin(acurr / 2);
  }
  if(style == 2) {
    return sin((acurr / 5.25) + (2 * pi) / 5.25);
  }
  if(style == 3) {
    return sin(acurr / 5.33333333333333);
  }
  if(style == 4) {
    return sin((acurr / 5.25) + ((2 * pi) / 4));
  }
  if(style == 5) {
    return pat(acurr, 1, (1 / 5.25), 0, (2 * pi) / 4, 0);
  }
  if(style == 6) {
    return pat(acurr, 0.5, 0, (1.0 / 3.0), 1, 0.5);
  }
  if(style == 7) {
    return pat(acurr, 1, (1 / 5.25), (2 * pi) / 16.0, 0, 0);
  }
  if(style == 8) {
    return 0.5;
  }
  return 0.5;
}



void spiro2(unsigned rad, unsigned steps, unsigned astyle, unsigned rstyle, color **pix, color colo) {
  if(rstyle == 8) {
    float a = ((float) rand() / (float) RAND_MAX);
    float b = ((float) rand() / (float) RAND_MAX) * 10;
    float c = (2 * pi) * ((float) rand() / (float) RAND_MAX);
    float d = (2 * pi) * ((float) rand() / (float) RAND_MAX);
    float e = ((1 - a) * ((float) rand() / (float) RAND_MAX);
    printf("[|a|b|c|d|e|]: |%f| |%f| |%f| |%f| |%f|\n", a, b, c, d, e);
  }

  point pt;
  color c = {0, 0, 0};
  if(colo.r == 255 && colo.g == 255 && colo.b == 255) {
    c = c;
  } else {
    c = colo;
  }
  float ang = 0;
  float r = 0.5;
  unsigned xx;
  unsigned yy;

  for(int t=0; t<steps; t++) {
    ang = aeq(t, ang, astyle);
    //printf("\tAng:%f\n", ang);
    if(rstyle == 8) {
      r = pat(ang, a, b, c, d, e);
    } else {
      r = req(t, ang, r, rstyle);
    }
    if(r < 0) {
      r = 0;
    } else {
      if(r > 1) {
        r = 1;
      }
    }
    //printf("\tR:%f\n", r);
    pt.x = ((rad * r) * cos(ang)) + rad;
    pt.y = ((rad * r) * sin(ang)) + rad;
    //printf("%f\t%f\n", pt.x, pt.y);
    xx = (unsigned) round(pt.x);
    yy = (unsigned) round(pt.y);
    //printf("%u\t%u\n", xx, yy);
    if(colo.r == 255 && colo.g == 255 && colo.b == 255) {
      c = next_color(c);
    }
    put_in_ppm(c, xx, yy, pix, rad);

  }
}





void make_ppm(color **pix, int widh) {
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


void random_pats(int num) {
  color c = {0, 0, 0};
  for(int i=0; i<num; i++) {
    c.b = (unsigned) round(255.0 / num) * i;
    spiro(




int main() {
  int rad = 500;
  int widh = (2 * rad) + 1;
  color **pix = blank(widh);
  circle(pix, widh);
  color c = {255, 255, 255};
  spiro2(rad, 100000, 0, 7, pix, c);
  //spiro2(rad, 100000, 0, 4, pix);
  //spiro2(rad, 100000, 0, 1, pix);
  //spiro2(rad, 100000, 0, 3, pix);

  make_ppm(pix, widh);

 return 0;
}
