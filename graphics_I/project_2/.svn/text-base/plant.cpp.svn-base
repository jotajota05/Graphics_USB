#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "plant.h"

using namespace std;

Plant::Plant(float x, float y, float z, float x_s, float y_s, float z_s) {  
  x_pos = x;
  y_pos = y;
  z_pos = z;
  x_scale = x_s;
  y_scale = y_s;
  z_scale = z_s;
}

void Plant::draw() {
  glPushMatrix();

  glTranslatef(x_pos, y_pos, z_pos);

  float factorxi, factorxf,factoryi, factoryf;

  factoryi = (y_pos - y_scale) / 44;
  factoryf = (y_pos + y_scale) / 44;
  factorxi = (x_pos - x_scale) / 80;
  factorxf = (x_pos + x_scale) / 80;
  
  glDisable(GL_TEXTURE_2D);
  glPushMatrix();
  
  glPushMatrix();
  glTranslatef(0,-10,0);
  glColor3f(0.54,0.14,0.0);
  glRotatef(90,-1.0,0.0,0.0);
  gluCylinder(gluNewQuadric(),2,2,4,20,20);
  glPopMatrix();
  
  glPushMatrix();
  glColor3f(0.0,0.0,0.0);
  glTranslatef(0,-6.3,0);
  glRotatef(90,-1.0,0.0,0.0);
  gluCylinder(gluNewQuadric(),1.98,0.001,0.5,20,20);
  glPopMatrix();
  
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);

  glPushMatrix();

  glScalef(x_scale, y_scale, z_scale);
  //Back
  glBegin(GL_TRIANGLES);						
  glNormal3f(0.0,0.0,-1.0);
  glTexCoord2f(factorxf, factoryf); glVertex3f( 0.0f, 1.0f, -1.0f);
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, -1.0f);
  glTexCoord2f(factorxi, factoryi); glVertex3f(-1.0f,-1.0f, -1.0f);
  glEnd();
  
  //Front
  glBegin(GL_TRIANGLES);						
  glNormal3f(0.0,0.0,1.0);
  glTexCoord2f(factorxf, factoryf); glVertex3f( 0.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, 1.0f);				
  glTexCoord2f(factorxi, factoryi); glVertex3f(-1.0f,-1.0f, 1.0f);				
  glEnd();
  glPopMatrix();

  glPushMatrix();

  glScalef(z_scale, y_scale,x_scale);
  glRotatef(90,0.0,1.0,0.0);
  //Back
  glBegin(GL_TRIANGLES);						
  glNormal3f(0.0,0.0,-1.0);
  glTexCoord2f(factorxf, factoryf); glVertex3f( 0.0f, 1.0f, -1.0f);
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, -1.0f);
  glTexCoord2f(factorxi, factoryi); glVertex3f(-1.0f,-1.0f, -1.0f);
  glEnd();
  
  //Front
  glBegin(GL_TRIANGLES);						
  glNormal3f(0.0,0.0,1.0);
  glTexCoord2f(factorxf, factoryf); glVertex3f( 0.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, 1.0f);				
  glTexCoord2f(factorxi, factoryi); glVertex3f(-1.0f,-1.0f, 1.0f);				
  glEnd();
  glPopMatrix();

  glPopMatrix();
}
