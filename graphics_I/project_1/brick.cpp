#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "brick.h"

using namespace std;

Brick::Brick() {
  x = 0.0;
  z = 0.0;
  red = 1.0;
  green = 0.498;
  blue = 0.0;
  life = 1;
  bonus.first = 0;
  bonus.second = 0;
  type = 0;
  matrix_pos.first = 0;
  matrix_pos.second = 0;
}

void Brick::draw() {
  glPushMatrix();
  glColor3f(red, green, blue); //this will set the square to red.  
  glTranslatef(x, 0.5, z);
  glScalef(2.0, 1.0, 1.0);
  glutSolidCube(1.0);
  glPopMatrix();
}

int Brick::equal(Brick* b) {
  if (x == b->x && z == b->z)
    return 1;
  else
    return 0;
}

int Brick::compare(vector<Brick*> bricks) {
  vector<Brick*>::iterator it;

  for (it = bricks.begin(); it != bricks.end(); it++) {
    if (equal((*it)))
      return 0;
  }

  return 1;
}
