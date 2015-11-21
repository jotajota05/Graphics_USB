#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "structure.h"
#include "base.h"

using namespace std;

Base::Base(float x, float y, float z, float x_s, float y_s, float z_s) {
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
}

void Base::draw() {

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glTranslatef(x_pos, y_pos, z_pos);
  glScalef(x_scale, y_scale, z_scale);

  Structure* s[3];
  s[0] = new Structure(0,0,0,50,10,15,0,0,0,0,1);
  s[0]->draw();
  s[1] = new Structure(0,0,15,50,20,15,0,0,0,0,1);
  s[1]->draw();
  s[2] = new Structure(0,0,30,50,30,15,0,0,0,0,1);
  s[2]->draw();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

}
