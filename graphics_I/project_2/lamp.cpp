#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <stdarg.h>

#include "lamp.h"

using namespace std;

Lamp::Lamp(int number, int t, int rot, float x1,float y1,float z1, float la_x, float la_y, float la_z, float la_ex, float ld_x, float ld_y, float ld_z, float ld_ex) {
  num = number;
  rotation = rot;
  type = t;
  x = x1;
  y = y1;
  z = z1;
  light_ambient[0] = la_x;
  light_ambient[1] = la_y;
  light_ambient[2] = la_z;
  light_ambient[3] = la_ex;
  light_diffuse[0] = ld_x;
  light_diffuse[1] = ld_y;
  light_diffuse[2] = ld_z;
  light_diffuse[3] = ld_ex;
}

void Lamp::assign_light() {
  float position[4];
  position[0] = x;
  position[2] = z;
  position[3] = 1.0;
  if (type == 0)
    position[1] = y+17;
  else if (type == 1) {
    position[1] = y;
  }

  switch (num) {
  case 1:
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);  
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);  
    glLightfv(GL_LIGHT1, GL_POSITION, position); 
    glEnable(GL_LIGHT1);
  case 2:
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);  
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);  
    glLightfv(GL_LIGHT2, GL_POSITION, position); 
    glEnable(GL_LIGHT2);
  case 3:
    glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);  
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);  
    glLightfv(GL_LIGHT3, GL_POSITION, position); 
    glEnable(GL_LIGHT3);
  case 4:
    glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient);  
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);  
    glLightfv(GL_LIGHT4, GL_POSITION, position); 
    glEnable(GL_LIGHT4);
  case 5:
    glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient);  
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);  
    glLightfv(GL_LIGHT4, GL_POSITION, position); 
    glEnable(GL_LIGHT4);
  case 6:
    glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient);  
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);  
    glLightfv(GL_LIGHT4, GL_POSITION, position); 
    glEnable(GL_LIGHT4);

  }
}

void Lamp::draw() {
  glPushMatrix();
  assign_light();
  glTranslatef(x,y,z);

  if (type == 0) {
    glScalef(1,1,1);
  
    glPushMatrix();
    glColor3f(0.54,0.14,0.0);
    glRotatef(90,-1.0,0.0,0.0);
    gluCylinder(gluNewQuadric(),0.15,0.15,10,20,20);
    gluCylinder(gluNewQuadric(),2,0.15,1,20,20);
    glPopMatrix();
  
    glPushMatrix();
    glTranslatef(0.0,10.0,0.0);
    glColor3f(0.93,0.86,0.504);

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(1.4,2.0,-1.4);
    glVertex3f(-1.4,2.0,-1.4);
    glVertex3f(-1.0,0.0,-1.0);
    glEnd();
  
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(-1.0,0.0,1.0);
    glVertex3f(-1.4,2.0,1.4);
    glVertex3f(1.4,2.0,1.4);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-1.0,0.0,1.0);
    glVertex3f(-1.4,2.0,1.4);
    glVertex3f(-1.4,2.0,-1.4);
    glVertex3f(-1.0,0.0,-1.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(1.4,2.0,1.4);
    glVertex3f(1.4,2.0,-1.4);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(1.0,0.01,1.0);
    glVertex3f(1.0,0.01,-1.0);
    glVertex3f(-1.0,0.01,-1.0);
    glVertex3f(-1.0,0.01,1.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(1.0,-0.01,1.0);
    glVertex3f(1.0,-0.01,-1.0);
    glVertex3f(-1.0,-0.01,-1.0);
    glVertex3f(-1.0,-0.01,1.0);
    glEnd();
    glPopMatrix();
  }
  else if (type == 1) {
    glColor3f(0.93,0.86,0.504);
    glRotatef(rotation, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-1.0,0.0,0.5);
    glVertex3f(-1.0,0.0,-0.5);
    glVertex3f(-1.7,1.7,-0.9);
    glVertex3f(-1.7,1.7,0.9);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.0,1.7,-0.9);
    glVertex3f(0.0,0.0,-0.5);
    glVertex3f(-1.0,0.0,-0.5);
    glVertex3f(-1.7,1.7,-0.9);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(0.0,1.7,0.9);
    glVertex3f(0.0,0.0,0.5);
    glVertex3f(-1.0,0.0,0.5);
    glVertex3f(-1.7,1.7,0.9);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.5);
    glVertex3f(0.0,0.0,-0.5);
    glVertex3f(-1.0,0.0,-0.5);
    glVertex3f(-1.0,0.0,0.5);
    glEnd();
  }
  glPopMatrix();

}
