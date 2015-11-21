#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "structure.h"
#include "railing.h"

using namespace std;

Railing::Railing(float x, float y, float z, float x_s, float y_s, float z_s) {
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
}

void Railing::draw() {

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glTranslatef(x_pos, y_pos, z_pos);
  glScalef(x_scale, y_scale, z_scale);

  Structure* base;
  base = new Structure(0,10,0,100,5,5,0,0,0,0,0);
  base->draw();
  Structure* post[9];
  int p = 0;
  int x = 10;
  for (p = 0; p < 9; p++) {
    post[p] = new Structure(x,0,0,1,10,1,0,0,0,0,0);
    post[p]->draw();
    x += 10;
  }

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

}
