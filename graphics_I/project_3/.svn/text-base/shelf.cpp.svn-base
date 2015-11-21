#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "structure.h"
#include "shelf.h"

using namespace std;

Shelf::Shelf(float x, float y, float z, float x_s, float y_s, float z_s, float x_r, float y_r, float z_r, float r) {
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
  x_rot = x_r;
  y_rot = y_r;
  z_rot = z_r;
  rot = r;
}

void Shelf::draw() {

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glTranslatef(x_pos, y_pos, z_pos);
  glRotatef(rot, x_rot, y_rot, z_rot);
  glScalef(x_scale, y_scale, z_scale);

  Structure* base;
  base = new Structure(1,1,1,1,1,1,0,0,0,0,0);
  base->draw();
 
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

}
