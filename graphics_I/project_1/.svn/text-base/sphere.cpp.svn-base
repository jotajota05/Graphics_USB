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

#include "sphere.h"
#include "vector.h"

#define PI 3.14159265

int timer = 100.0;


using namespace std;

Sphere::Sphere() {
  srand(time(NULL));
  float num1 = (rand()/(RAND_MAX*0.5));
  pair < float,float > dir2;
  dir.first = 18;
  dir.second = 8;
  dir2.first = normalize(dir).first;
  dir2.second = normalize(dir).second;
  int num2 = floor((rand()/(RAND_MAX*0.5)));
  z = floor((8 + (dir2.second+0.1)*num1)*10) / 10;
  radius = 0.6;
  speed = 30.0;
  if (num2 == 1) {
    x = floor((18 - (dir2.first+0.1)*num1)*10) / 10;
    r = 1;l = 0;
  }
  else {
    x = floor((18 + (dir2.first+0.1)*num1)*10) / 10;
    r = 0;l = 1;
  }
  u = 1;
  d = 0;
  hit_bar = 0;
  lose_timer = 3000;
}

void Sphere::draw() {
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(x, 0.5, z);
  glutSolidSphere(radius,50.0,50.0);
  glPopMatrix();
}

void Sphere::move_to() {
  pair < float,float > dir2;
  int div;

  timer -= 0.02;
  
  if (timer <= speed) {
    timer = 100.0;
    if (x > 1 && x < 35 && z > 1 && z < 60 && hit_bar == 0) {
      if (u == 1 && l == 1) {
	x = floor((x + 0.3)*10)/10;
	z = floor((z + 0.3)*10)/10;
	dir.first = x;
	dir.second = z;
      }
      else if (d == 1 && l == 1) {
	x = floor((x + 0.3)*10)/10;
	z = floor((z - 0.3)*10)/10;
	dir.first = x;
	dir.second = z;
      } 
      else if (u == 1 && r == 1) {
	x = floor((x - 0.3)*10)/10;
	z = floor((z + 0.3)*10)/10;
	dir.first = x;
	dir.second = z;
      } 
      else if (d == 1 && r == 1) {
	x = floor((x - 0.3)*10)/10;
	z = floor((z - 0.3)*10)/10;
	dir.first = x;
	dir.second = z;
      }
    } else {
      dir2.first = normalize(dir).first;
      dir2.second = normalize(dir).second;
      float num = (rand()/(RAND_MAX*0.5));
      if (x-radius <= 1) { 
	l = 1;
	r = 0;
	x = floor((x + (dir2.first+0.1)*num)*10) / 10;
      } 
      else if (x+radius >= 35) { 
	r = 1;
	l = 0;
	x = floor((x - (dir2.first+0.1)*num)*10) / 10;
      }
      else if (z+radius >= 60) { 
	d = 1;
	u = 0;
	z = floor((z - (dir2.second+0.1)*num)*10) / 10;
      } else if (z-radius <= 1) {
	hit_bar = 0;
	lose_timer = 3000;
	srand(time(NULL));
	float num1 = (rand()/(RAND_MAX*0.5));
	pair < float,float > dir2;
	dir.first = 18;
	dir.second = 8;
	dir2.first = normalize(dir).first;
	dir2.second = normalize(dir).second;
	int num2 = floor((rand()/(RAND_MAX*0.5)));
	z = floor((8 + (dir2.second+0.1)*num1)*10) / 10;
	radius = 0.6;
	speed = 30.0;
	if (num2 == 1) {
	  x = floor((18 - (dir2.first+0.1)*num1)*10) / 10;
	  r = 1;l = 0;
	}
	else {
	  x = floor((18 + (dir2.first+0.1)*num1)*10) / 10;
	  r = 0;l = 1;
	}
	u = 1;
	d = 0;
	
	cout << "Perdiste!, Vuelve a intentarlo.\n";
      }
      else if (hit_bar == 1) { 
	u = 1;
	d = 0;
	z = floor((z + (dir2.second+0.1)*num)*10) / 10;
	hit_bar = 0;
      }
      else if (hit_bar == 2) { 
	u = 0;
	d = 1;
	r = 0;
	l = 1;
	z = floor((z - (dir2.second+0.1)*num)*10) / 10;
	hit_bar = 0;
      }
      else if (hit_bar == 3) { 
	u = 0;
	d = 1;
	r = 1;
	l = 0;
	z = floor((z - (dir2.second+0.1)*num)*10) / 10;
	hit_bar = 0;
      }
    }
  }
}

bool Sphere::hit_brick(Brick* bricky) {
  pair < float,float > dir2;
  dir2.first = normalize(dir).first;
  dir2.second = normalize(dir).second;
  float num = (rand()/(RAND_MAX*0.5));
  double dist = sin(45.0*PI/180);
  dist *= radius;

  if (x-radius-0.08 <= bricky->x+1.1 &&
      x-radius-0.08 >= bricky->x-1.1 &&
      z >= bricky->z-0.6 &&
      z <= bricky->z+0.6) { 
    l = 1;
    r = 0;
    x = floor((x + (dir2.first+0.1)*num)*10) / 10;
    return 1;
  }
  else if (x+radius+0.08 >= bricky->x-1.1 &&
	   x+radius+0.08 <= bricky->x+1.1 &&
	   z >= bricky->z-0.6 &&
	   z <= bricky->z+0.6) { 
    r = 1;
    l = 0;
    x = floor((x - (dir2.first+0.1)*num)*10) / 10;
    return 1;
  }
  else if (z+radius+0.08 >= bricky->z-0.6 &&
	   z+radius+0.08 <= bricky->z+0.6 &&
	   x <= bricky->x+1.1 &&
	   x >= bricky->x-1.1) { 
    d = 1;
    u = 0;
    z = floor((z - (dir2.first+0.1)*num)*10) / 10;
    return 1;
  }
  else if (z-radius-0.08 <= bricky->z+0.6 &&
	   z-radius-0.08 >= bricky->z-0.6 && 
	   x <= bricky->x+1.1 &&
	   x >= bricky->x-1.1) { 
    u = 1;
    d = 0;
    z = floor((z + (dir2.first+0.1)*num)*10) / 10;
    return 1;
  } 
  else if (x+dist+0.08 >= bricky->x-1.1 &&
	   x+dist+0.08 <= bricky->x+1.1 &&
	   z+dist+0.08 >= bricky->z-0.6 &&
	   z+dist+0.08 <= bricky->z+0.6) {
    r = d = 1;
    l = u = 0;
    x = floor((x - (dir2.second+0.1)*num)*10) / 10;
    z = floor((z - (dir2.second+0.1)*num)*10) / 10;
    return 1;
  }
  else if (x-dist-0.08 <= bricky->x+1.1 &&
	   x-dist-0.08 >= bricky->x-1.1 &&
	   z-dist-0.08 <= bricky->z+0.6 &&
	   z-dist-0.08 >= bricky->z-0.6) {
    r = d = 0;
    l = u = 1;
    x = floor((x + (dir2.second+0.1)*num)*10) / 10;
    z = floor((z + (dir2.second+0.1)*num)*10) / 10;
    return 1;
  }
  else if (x-dist-0.08 <= bricky->x+1.1 &&
	   x-dist-0.08 >= bricky->x-1.1 &&
	   z+dist+0.08 >= bricky->z-0.6 &&
	   z+dist+0.08 <= bricky->z+0.6) {
    l = d = 1;
    r = u = 0;
    x = floor((x + (dir2.second+0.1)*num)*10) / 10;
    z = floor((z - (dir2.second+0.1)*num)*10) / 10;
    return 1;
  }
  else if (x+dist+0.08 >= bricky->x-1.1 &&
	   x+dist+0.08 <= bricky->x+1.1 &&
	   z-dist-0.08 <= bricky->z+0.6 &&
	   z-dist-0.08 >= bricky->z-0.6) { 
    l = d = 0;
    r = u = 1;
    x = floor((x - (dir2.second+0.1)*num)*10) / 10;
    z = floor((z + (dir2.second+0.1)*num)*10) / 10;
    return 1;
  }
  return 0;
}

