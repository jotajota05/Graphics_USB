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

Lamp::Lamp(int number, float x1, float y1, float z1) {
  num = number;
  x = x1;
  y = y1;
  z = z1;
}

void Lamp::assign_light() {
  GLfloat spot_direction[] = {0.0, -1.0, 0.0};
  GLint spot_exponent = 180;
  GLint spot_cutoff = 12;
  GLfloat Kc= 1.0;
  GLfloat Kl = 0.0;
  GLfloat Kq = 0.0;

  GLfloat PositionLight[] = {x, y, z, 1.0};
  GLfloat DiffuseLight[] = {1, 1, 1, 1}; 
  GLfloat AmbientLight[] = {1, 1, 1, 1}; 
  GLfloat SpecularLight[] = {1 ,1, 1, 1 }; 
  
  switch (num) {
  case 0:
    glLightfv (GL_LIGHT2, GL_POSITION, PositionLight); 
    glLightfv (GL_LIGHT2, GL_AMBIENT, AmbientLight); 
    glLightfv (GL_LIGHT2, GL_DIFFUSE, DiffuseLight); 
    glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction); 
    glLighti(GL_LIGHT2, GL_SPOT_EXPONENT, spot_exponent); 
    glLighti(GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutoff); 
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, Kc); 
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, Kl); 
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, Kq); 

    glEnable(GL_LIGHT2);

  break;
  case 1:
    glLightfv (GL_LIGHT3, GL_POSITION, PositionLight); 
    glLightfv (GL_LIGHT3, GL_AMBIENT, AmbientLight); 
    glLightfv (GL_LIGHT3, GL_DIFFUSE, DiffuseLight); 
    glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight);

    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction); 
    glLighti(GL_LIGHT3, GL_SPOT_EXPONENT, spot_exponent); 
    glLighti(GL_LIGHT3, GL_SPOT_CUTOFF, spot_cutoff); 
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, Kc); 
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, Kl); 
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, Kq); 

    glEnable(GL_LIGHT3);

    break;
  case 2:
    glLightfv (GL_LIGHT4, GL_POSITION, PositionLight); 
    glLightfv (GL_LIGHT4, GL_AMBIENT, AmbientLight); 
    glLightfv (GL_LIGHT4, GL_DIFFUSE, DiffuseLight); 
    glLightfv(GL_LIGHT4, GL_SPECULAR, SpecularLight);

    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction); 
    glLighti(GL_LIGHT4, GL_SPOT_EXPONENT, spot_exponent); 
    glLighti(GL_LIGHT4, GL_SPOT_CUTOFF, spot_cutoff); 
    glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, Kc); 
    glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, Kl); 
    glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, Kq); 

    glEnable(GL_LIGHT4);

    break;
  case 3:
    glLightfv (GL_LIGHT5, GL_POSITION, PositionLight); 
    glLightfv (GL_LIGHT5, GL_AMBIENT, AmbientLight); 
    glLightfv (GL_LIGHT5, GL_DIFFUSE, DiffuseLight); 
    glLightfv(GL_LIGHT5, GL_SPECULAR, SpecularLight);

    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_direction); 
    glLighti(GL_LIGHT5, GL_SPOT_EXPONENT, spot_exponent); 
    glLighti(GL_LIGHT5, GL_SPOT_CUTOFF, spot_cutoff); 
    glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, Kc); 
    glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, Kl); 
    glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, Kq); 

    glEnable(GL_LIGHT5);
    break;
  case 4:
    glLightfv (GL_LIGHT6, GL_POSITION, PositionLight); 
    glLightfv (GL_LIGHT6, GL_AMBIENT, AmbientLight); 
    glLightfv (GL_LIGHT6, GL_DIFFUSE, DiffuseLight); 
    glLightfv(GL_LIGHT6, GL_SPECULAR, SpecularLight);

    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction); 
    glLighti(GL_LIGHT6, GL_SPOT_EXPONENT, spot_exponent); 
    glLighti(GL_LIGHT6, GL_SPOT_CUTOFF, spot_cutoff); 
    glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, Kc); 
    glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, Kl); 
    glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, Kq); 

    glEnable(GL_LIGHT6);

    break;
  case 5:
    glLightfv (GL_LIGHT7, GL_POSITION, PositionLight); 
    glLightfv (GL_LIGHT7, GL_AMBIENT, AmbientLight); 
    glLightfv (GL_LIGHT7, GL_DIFFUSE, DiffuseLight); 
    glLightfv(GL_LIGHT7, GL_SPECULAR, SpecularLight);

    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spot_direction); 
    glLighti(GL_LIGHT7, GL_SPOT_EXPONENT, spot_exponent); 
    glLighti(GL_LIGHT7, GL_SPOT_CUTOFF, spot_cutoff); 
    glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, Kc); 
    glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, Kl); 
    glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, Kq); 

    glEnable(GL_LIGHT7);

    break;
  }

}

void Lamp::draw() {
  glPushMatrix();
  glColor3f(0.7,0.7,0.7);
  glTranslatef(x,y,z);
  glRotatef(90,-1.0,0.0,0.0);
  gluCylinder(gluNewQuadric(),3,0.5,3,30,30);
  glPushMatrix();
  glColor3f(1,1,0);
  glutSolidSphere(1, 30, 30);
  glPopMatrix();
  glPopMatrix();

}
