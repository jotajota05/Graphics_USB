#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "structure.h"

using namespace std;

// El ultimo booleano decide si la estructura se va a dividir en pequehos cuadros para la iluminacion spotligth o no.
Structure::Structure(float x, float y, float z, float x_s, float y_s, float z_s, bool x_r, bool y_r, bool z_r, float r, bool f) {  
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
  x_rotate = x_r;
  y_rotate = y_r;
  z_rotate = z_r;
  rotation = r;
  flag = f;
}

void Structure::draw() {

  glPushMatrix();
  glTranslatef(x_pos, y_pos, z_pos);
  glRotatef(rotation, x_rotate, y_rotate, z_rotate);
  glScalef(x_scale, y_scale, z_scale);
  
  int side = 0;
  float i, j = 0.0;
  float div;
  if (flag == 1)
    div = 60.0;
  else  div = 1;
  float rate = 1.0 / div;
  float rot, xr, yr, zr, xt, yt, zt = 0.0;

  for (side = 0; side < 6; side++) {

    switch(side) {
    case 0: 
      rot = 0.0; xr = 0.0; yr = 0.0; zr = 0.0;
      xt = 0.0; yt = 0.0; zt = 0.0;
      break;
    case 1: 
      rot = 0.0; xr = 0.0; yr = 0.0; zr = 0.0;
      xt = 0.0; yt = 0.0; zt = 1.0;
      break;
    case 2: 
      rot = -90.0; xr = 0.0; yr = 1.0; zr = 0.0;
      xt = 0.0; yt = 0.0; zt = 0.0;
      break;
    case 3: 
      rot = -90.0; xr = 0.0; yr = 1.0; zr = 0.0;
      xt = 0.0; yt = 0.0; zt = -1.0;
      break;
    case 4: 
      rot = 90.0; xr = 1.0; yr = 0.0; zr = 0.0;
      xt = 0.0; yt = 0.0; zt = 0.0;
      break;
    case 5: 
      rot = 90.0; xr = 1.0; yr = 0.0; zr = 0.0;
      xt = 0.0; yt = 0.0; zt = -1.0;
      break;
    }
    i = 0;
    j = 0;
    glPushMatrix();
    glRotatef(rot, xr, yr, zr);
    glTranslatef(xt, yt, zt);
    glBegin(GL_QUADS);						  
    while (i < 1.0) {
      while (j < 1.0) {
        glNormal3f(0.0,0.0,1.0);
        glTexCoord2f(i, j); glVertex3f(i , j, 0.0f);
        glTexCoord2f(i+rate, j); glVertex3f(i+rate , j, 0.0f);
        glTexCoord2f(i+rate, j+rate); glVertex3f(i+rate , j+rate, 0.0f);
        glTexCoord2f(i, j+rate); glVertex3f(i , j+rate, 0.0f);
        j += rate;
      }
      i += rate;
      j = 0;
    }
    glEnd();
    glPopMatrix();
        
  }
  
  glPopMatrix();

}
