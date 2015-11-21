#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "structure.h"
#include "box.h"

using namespace std;

Box::Box(float x, float y, float z, float x_s, float y_s, float z_s) {
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
}

void Box::draw(int* texture) {

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glTranslatef(x_pos, y_pos, z_pos);
  glScalef(x_scale, y_scale, z_scale);

  Structure* s[4];
  
  glBindTexture(GL_TEXTURE_2D, texture[8]);
  s[0] = new Structure(0,0,0,5,60,70,0,1,0,20,0);
  s[0]->draw();
  glBindTexture(GL_TEXTURE_2D, texture[9]);
  s[1] = new Structure(120,0,0,5,60,70,0,1,0,-20,0);
  s[1]->draw();
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  s[2] = new Structure(28,0,60,70,60,5,0,0,0,0,0);
  s[2]->draw();
  glBindTexture(GL_TEXTURE_2D, texture[7]);  
s[3] = new Structure(-5,60,-10,130,5,90,0,0,0,0,0);
  s[3]->draw();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

}
