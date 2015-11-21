#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "structure.h"
#include "objetive.h"

using namespace std;

Objetive::Objetive(float x, float y, float z, float x_s, float y_s, float z_s) {
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
}

void Objetive::draw() {

  glPushMatrix();
  glTranslatef(x_pos, y_pos, z_pos);
  glScalef(x_scale, y_scale, z_scale);
  Structure* s[2];
  glEnable(GL_TEXTURE_2D);
  s[0] = new Structure(0,0,0,30,30,0,0,0,0,0,0);
  s[0]->draw();
  glDisable(GL_TEXTURE_2D);
  s[0] = new Structure(12.5,-5,-2.5,5,10,5,0,0,0,0,0);
  s[0]->draw();

  glPopMatrix();

}

void Objetive::move(string dir) {
  float min = 50;
  float max = 175;
  if (dir == "R") {
    x_pos -= 0.5;
    if (x_pos <= min) 
      x_pos = max;
  } else {
    x_pos += 0.5;
    if (x_pos >= max) 
      x_pos = min;
  }
}
