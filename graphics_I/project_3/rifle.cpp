#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "rifle.h"

using namespace std;


Rifle::Rifle(float x, float y, float z, float x_s, float y_s, float z_s) {
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
}

void Rifle::draw() {

  glPushMatrix();
  glTranslatef(x_pos, y_pos, z_pos);
  glScalef(x_scale, y_scale, z_scale);
  
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
  
  glLoadIdentity();
  glColor3ub(255,0,255);
  glPushMatrix();
  glTranslatef(0,-0.05,-0.0);
  glScalef(0.015,0.015,1);
  glutSolidCube(1);
  glPopMatrix();
    
  glColor3ub(0,0,255);
  glPushMatrix();
  glTranslatef(0,0.0,-0.4);
  glScalef(0.025,0.025,0.1);
  glutSolidTorus ( 0.05,  0.5, 20, 20);
  glPopMatrix();
    
  glColor3ub(0,0,0);
  glPushMatrix();
  glTranslatef(0,-0.025,-0.4);
  glScalef(0.007,0.02,0.007);
  glutSolidCube(1);
  glPopMatrix();

  glPopMatrix();

}
