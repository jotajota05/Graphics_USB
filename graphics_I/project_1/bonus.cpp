#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "bonus.h"

using namespace std;

int bigger = 0;

Bonus::Bonus(Brick* brick) {
  active = 1;
  bricky = brick;
  x = brick->x;
  z = brick->z-0.6;
  type = brick->bonus.second;
}

void Bonus::draw() {
  if (active == 1) {
    glPushMatrix();
    if (type == 0)
      glColor3f(1.0,0.0,0.0);
    else if (type == 1)
      glColor3f(0.0,0.0,1.0);
    glTranslatef(x,0.5,z);
    glutSolidTorus(0.2,0.4,50,50);
    glPopMatrix();
  }
}

void Bonus::drop() {
  if (active == 1)
    if (z >= 0.3)
      z -= 0.01;
    else active = 0;
}

void Bonus::set_bonus(Base* bar, Sphere* ball) {
  if (z <= (bar->z)+0.6 && 
      z >= (bar->z)+0.4 && 
      x > (bar->x - bar->longt/2) && 
      x < (bar->x + bar->longt/2)) {
    if (type == 0 && bigger < 2) {
      bigger++;
      bar->longt += bar->longt*0.1;  
    } else if (type == 1) {
      ball->speed += ball->speed*0.5;
    }
    active = 0; 
  }
}
