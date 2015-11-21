#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include <math.h>

#include "bullet.h"

using namespace std;


Bullet::Bullet(double* punto1, double* punto2, double alfa1_ini) {
  p1 = punto1;
  p2 = punto2;
  alfa1 = alfa1_ini;
  alfa2 = alfa1 - 0.03;
  alfa3 = alfa2 - 0.03;
  p3 = (double*)malloc(sizeof(double)*3);
  p3[0] = 0.0;
  p3[1] = 0.0;
  p3[2] = 0.0;
  p4 = (double*)malloc(sizeof(double)*3);
  p4[0] = 0.0;
  p4[1] = 0.0;
  p4[2] = 0.0;
}

void Bullet::draw() {
  glColor3f(1.0,1.0,1.0);

  double* position1_1 = scalarProduct(alfa1, p1);
  double* position1_2 = scalarProduct(1 - alfa1, p2);
  
  double* position2_1 = scalarProduct(alfa2, p1);
  double* position2_2 = scalarProduct(1 - alfa2, p2);

  double* position3_1 = scalarProduct(alfa3, p1);
  double* position3_2 = scalarProduct(1 - alfa3, p2);

  double* final_p1 = suma(position1_1, position1_2);
  p3 = final_p1;
  double* final_p2 = suma(position2_1, position2_2);
  double* final_p3 = suma(position3_1, position3_2);
  p4 = final_p3;

  glPushMatrix();
  glTranslatef(final_p2[0], final_p2[1], final_p2[2]);
  glutSolidSphere(0.5, 20, 20);
  glPopMatrix();
      
}

double* Bullet::scalarProduct(double alfa, double* point) {
  double* new_b = (double*)malloc(sizeof(double)*3);

  new_b[0] = point[0]*alfa;
  new_b[1] = point[1]*alfa;
  new_b[2] = point[2]*alfa;

  return new_b;
}

double* Bullet::suma(double* point1, double* point2) {
  double* new_b = (double*)malloc(sizeof(double)*3);

  new_b[0] = point1[0] + point2[0];
  new_b[1] = point1[1] + point2[1];
  new_b[2] = point1[2] + point2[2];  
  
  return new_b;
}

void Bullet::updateAlfa() {
  alfa1 -= 0.1;
  alfa2 -= 0.1;
  alfa3 -= 0.1;
}
