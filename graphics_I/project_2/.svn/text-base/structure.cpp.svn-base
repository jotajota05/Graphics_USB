#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "structure.h"

using namespace std;

Structure::Structure(float x, float y, float z, float x_s, float y_s, float z_s, bool x_r, bool y_r, bool z_r, float r, string f) {  
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

  float factorxi, factorxf,factoryi, factoryf;

  factoryi = (y_pos - y_scale) / 44;
  factoryf = (y_pos + y_scale) / 44;
  
  if (flag == "front") {
    factorxi = (x_pos - x_scale) / 80;
    factorxf = (x_pos + x_scale) / 80;
  } else 
    if (flag == "rear") {
      factorxi = (z_pos - z_scale) / 80;
      factorxf = (z_pos + z_scale) / 80;
    } else {
      factorxi = 0.0;
      factorxf = 1.0;
      factoryi = 0.0;
      factoryf = 1.0;
    }

  //Back
  glBegin(GL_QUADS);						
  glNormal3f(0.0,0.0,-1.0);
  glTexCoord2f(factorxi, factoryf); glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(factorxf, factoryf); glVertex3f( 1.0f, 1.0f, -1.0f);
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, -1.0f);
  glTexCoord2f(factorxi, factoryi); glVertex3f(-1.0f,-1.0f, -1.0f);
  glEnd();
  
  //Front
  glBegin(GL_QUADS);						
  glNormal3f(0.0,0.0,1.0);
  glTexCoord2f(factorxi, factoryf); glVertex3f(-1.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryf); glVertex3f( 1.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, 1.0f);				
  glTexCoord2f(factorxi, factoryi); glVertex3f(-1.0f,-1.0f, 1.0f);				
  glEnd();

  //Top
  glBegin(GL_QUADS);						
  glNormal3f(0.0,1.0,0.0);
  glTexCoord2f(factorxi, factoryi); glVertex3f( 1.0f, 1.0f,-1.0f);				
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryf); glVertex3f(-1.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxi, factoryf); glVertex3f(-1.0f, 1.0f,-1.0f);				
  glEnd();

  //Bottom
  glBegin(GL_QUADS);		
  glNormal3f(0.0,-1.0,0.0);				
  glTexCoord2f(factorxi, factoryi); glVertex3f( 1.0f,-1.0f,-1.0f);				
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryf); glVertex3f(-1.0f,-1.0f, 1.0f);				
  glTexCoord2f(factorxi, factoryf); glVertex3f(-1.0f,-1.0f,-1.0f);				
  glEnd();

  //Left
  glBegin(GL_QUADS);		
  glNormal3f(1.0,0.0,0.0);									
  glTexCoord2f(factorxi, factoryf); glVertex3f( 1.0f, 1.0f,-1.0f);				
  glTexCoord2f(factorxf, factoryf); glVertex3f( 1.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryi); glVertex3f( 1.0f,-1.0f, 1.0f);				
  glTexCoord2f(factorxi, factoryi); glVertex3f( 1.0f,-1.0f,-1.0f);				
  glEnd();

  //Right
  glBegin(GL_QUADS);						
  glNormal3f(-1.0,0.0,0.0);					
  glTexCoord2f(factorxi, factoryf); glVertex3f(-1.0f, 1.0f,-1.0f);				
  glTexCoord2f(factorxf, factoryf); glVertex3f(-1.0f, 1.0f, 1.0f);				
  glTexCoord2f(factorxf, factoryi); glVertex3f(-1.0f,-1.0f, 1.0f);				
  glTexCoord2f(factorxi, factoryi); glVertex3f(-1.0f,-1.0f,-1.0f);				
  glEnd();
  glPopMatrix();
}
