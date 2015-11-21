#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "base.h"

using namespace std;

Base::Base() {
  x = 18;
  z = 4;
  longt = 6.0;
}

void Base::draw() {
  glPushMatrix();
  glColor3f(0.698,0.133,0.133);  
  glTranslatef(x, 0.5, z);
  glScalef(longt, 1.0, 1.0);
  glutSolidCube(1);
  glPopMatrix();

}

void Base::move_rigth() {
  if (x-longt/2 >= 0.7)
    x -= 1;
}

void Base::move_left() {
  if (x+longt/2 <= 35)
    x += 1;
}
