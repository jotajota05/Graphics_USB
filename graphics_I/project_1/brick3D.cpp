#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include <vector>
#include <list>
#include <math.h>

#include "brick.h"
#include "sphere.h"
#include "base.h"
#include "bonus.h"
#include "vector.h"

#define PI 3.14159265

using namespace std;

int camera_x = 18.0;
int camera_y = 15.0;
int camera_z = -15.0;
int camera_type = 2;
pair <char,int> keys[7];
vector< vector<Brick*> > brick_list;
Sphere* ball = new Sphere();;
Base* bar = new Base();
Bonus* bon[10];
int b = 0;
int first = 1;
bool flag = 0;
pair < int,int > bricky;
int pending_timer = 4500;
int win = 0;

void ejes() {
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0); // Eje X en rojo
  glVertex3f(200.0, 0.0, 0.0);
  glVertex3f(-200.0, 0.0, 0.0);
  glColor3f(0.0, 1.0, 0.0); // Eje Z en azul
  glVertex3f(0.0, 200.0, 0.0);
  glVertex3f(0.0, -200.0, 0.0);
  glColor3f(0.0, 0.0, 1.0); // Eje Y en verde
  glVertex3f(0.0, 0.0, 200.0);
  glVertex3f(0.0, 0.0, -200.0);
  glEnd();
}

void initGL(int width, int height) {		       
  glClearColor(0.0, 0.0, 0.0, 0.5);
  glClearDepth(1);
  glDepthFunc(GL_LESS);		
  glEnable(GL_DEPTH_TEST);		
  glShadeModel(GL_SMOOTH);	        
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();			
  gluPerspective(45.0, width/height, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void drawBackground(int x_worldSize, int z_worldSize) {
  glColor3f(0.0f,0.39f,0.0f);
  glBegin(GL_QUADS);		
  glVertex3f(0.0, -0.1, z_worldSize);
  glVertex3f(x_worldSize, 0.0, z_worldSize);
  glVertex3f(x_worldSize, 0.0, 0.0);
  glVertex3f(0.0, -0.1, 0.0);
  glEnd();
}

void initKeys() {
  keys[0].first = 'i';
  keys[0].second = 0;

  keys[1].first = 'k';
  keys[1].second = 0;

  keys[2].first = 'l';
  keys[2].second = 0;

  keys[3].first = 'j';
  keys[3].second = 0;

  keys[4].first = 'c';
  keys[4].second = 0;

  keys[5].first = 'a';
  keys[5].second = 0;

  keys[6].first = 'd';
  keys[6].second = 0;
}

void keyPressed(unsigned char key, int x, int y) {
  int i;
  for (i = 0; i < 7; i++) {
    if (keys[i].first == key) {
      keys[i].second = 1;
      break;
    }
  }
}

int searchKey(unsigned char key) {
  int i;
  
  for (i = 0; i < 7; i++) {
    if (keys[i].first == key) {
      return keys[i].second;
    }
  }

  return 0;
}
  
void keysFunc() {  
  if (searchKey('i')) // Camera X up
    camera_x += 1;
  if (searchKey('k')) // Camera X down
    camera_x -= 1;        
  if (searchKey('l')) // Camera z up
    camera_z += 1;
  if (searchKey('j')) // Camera z down
    camera_z -= 1;
  if (searchKey('c')) { // Camera z down
    if (camera_type == 1) {
      camera_type = 2;
      camera_x = 18;
      camera_y = 45.0;
      camera_z = 30;
    }
    else {
      camera_type = 1;
      camera_x = 18;
      camera_y = 15.0;
      camera_z = -15;
    }
  }
  if (searchKey('d'))
    bar->move_rigth();
  if (searchKey('a'))
    bar->move_left();

  initKeys();
}

void drawWalls() {
  //Pared izquierda
  glPushMatrix();
  glColor3f(0.545, 0.27, 0.074);
  glTranslatef(0.0, 0.6, 30.0);
  glScalef(1.0, 2.0, 120.0);
  glutSolidCube(0.5);
  glPopMatrix();

  //Pared derecha
  glPushMatrix();
  glColor3f(0.545, 0.27, 0.074);
  glTranslatef(36.0, 0.6, 30.0);
  glScalef(1.0, 2.0, 120.0);
  glutSolidCube(0.5);
  glPopMatrix();

  //Pared arriba
  glPushMatrix();
  glColor3f(0.545, 0.27, 0.074);
  glTranslatef(18.0, 0.6, 60.0);
  glRotatef(90, 0.0, 1.0, 0.0);
  glScalef(1.0, 2.0, 73.0);
  glutSolidCube(0.5);
  glPopMatrix();

}

void drawBricks() {
  vector< vector<Brick*> >::iterator row_it;
  vector<Brick*>::iterator col_it;
  
  int k = 0;
  
  for (row_it = brick_list.begin(); row_it != brick_list.end(); row_it++) {
    for (col_it = (*row_it).begin(); col_it != (*row_it).end(); col_it++) {
      if ((*col_it)->life == 1)
	(*col_it)->draw();
    }
  }
}

void displayBricks1() {
  brick_list.at(0).at(0)->x = 30;
  brick_list.at(0).at(0)->z = 54;

  brick_list.at(0).at(1)->x = 24;
  brick_list.at(0).at(1)->z = 54;

  brick_list.at(0).at(2)->x = 18;
  brick_list.at(0).at(2)->z = 54;

  brick_list.at(0).at(3)->x = 12;
  brick_list.at(0).at(3)->z = 54;

  brick_list.at(0).at(4)->x = 6;
  brick_list.at(0).at(4)->z = 54;

  brick_list.at(1).at(0)->x = 24;
  brick_list.at(1).at(0)->z = 48;

  brick_list.at(1).at(1)->x = 18;
  brick_list.at(1).at(1)->z = 48;

  brick_list.at(1).at(2)->x = 12;
  brick_list.at(1).at(2)->z = 48;

  brick_list.at(1).at(3)->x = 18;
  brick_list.at(1).at(3)->z = 42;

  brick_list.at(1).at(4)->x = 24;
  brick_list.at(1).at(4)->z = 36;

  brick_list.at(2).at(0)->x = 18;
  brick_list.at(2).at(0)->z = 36;

  brick_list.at(2).at(1)->x = 12;
  brick_list.at(2).at(1)->z = 36;

  brick_list.at(2).at(2)->x = 30;
  brick_list.at(2).at(2)->z = 30;

  brick_list.at(2).at(3)->x = 24;
  brick_list.at(2).at(3)->z = 30;

  brick_list.at(2).at(4)->x = 18;
  brick_list.at(2).at(4)->z = 30;

  brick_list.at(3).at(0)->x = 12;
  brick_list.at(3).at(0)->z = 30;

  brick_list.at(3).at(1)->x = 6;
  brick_list.at(3).at(1)->z = 30;

  brick_list.at(3).at(2)->x = 24;
  brick_list.at(3).at(2)->z = 24;

  brick_list.at(3).at(3)->x = 18;
  brick_list.at(3).at(3)->z = 24;

  brick_list.at(3).at(4)->x = 12;
  brick_list.at(3).at(4)->z = 24;

  brick_list.at(4).at(0)->x = 18;
  brick_list.at(4).at(0)->z = 18;

  brick_list.at(4).at(1)->x = 30;
  brick_list.at(4).at(1)->z = 42;

  brick_list.at(4).at(2)->x = 6;
  brick_list.at(4).at(2)->z = 42;

  brick_list.at(4).at(3)->x = 30;
  brick_list.at(4).at(3)->z = 18;

  brick_list.at(4).at(4)->x = 6;
  brick_list.at(4).at(4)->z = 18;
}

void displayBricks2() {
  brick_list.at(0).at(0)->x = 30;
  brick_list.at(0).at(0)->z = 45;

  brick_list.at(0).at(1)->x = 30;
  brick_list.at(0).at(1)->z = 36;

  brick_list.at(0).at(2)->x = 30;
  brick_list.at(0).at(2)->z = 27;

  brick_list.at(0).at(3)->x = 24;
  brick_list.at(0).at(3)->z = 51;

  brick_list.at(0).at(4)->x = 24;
  brick_list.at(0).at(4)->z = 45;

  brick_list.at(1).at(0)->x = 24;
  brick_list.at(1).at(0)->z = 39;

  brick_list.at(1).at(1)->x = 24;
  brick_list.at(1).at(1)->z = 33;

  brick_list.at(1).at(2)->x = 24;
  brick_list.at(1).at(2)->z = 27;

  brick_list.at(1).at(3)->x = 24;
  brick_list.at(1).at(3)->z = 21;

  brick_list.at(1).at(4)->x = 18;
  brick_list.at(1).at(4)->z = 54;

  brick_list.at(2).at(0)->x = 18;
  brick_list.at(2).at(0)->z = 48;

  brick_list.at(2).at(1)->x = 18;
  brick_list.at(2).at(1)->z = 42;

  brick_list.at(2).at(2)->x = 18;
  brick_list.at(2).at(2)->z = 36;

  brick_list.at(2).at(3)->x = 18;
  brick_list.at(2).at(3)->z = 30;

  brick_list.at(2).at(4)->x = 18;
  brick_list.at(2).at(4)->z = 24;

  brick_list.at(3).at(0)->x = 18;
  brick_list.at(3).at(0)->z = 18;

  brick_list.at(3).at(1)->x = 12;
  brick_list.at(3).at(1)->z = 51;

  brick_list.at(3).at(2)->x = 12;
  brick_list.at(3).at(2)->z = 45;

  brick_list.at(3).at(3)->x = 12;
  brick_list.at(3).at(3)->z = 39;

  brick_list.at(3).at(4)->x = 12;
  brick_list.at(3).at(4)->z = 33;

  brick_list.at(4).at(0)->x = 12;
  brick_list.at(4).at(0)->z = 27;

  brick_list.at(4).at(1)->x = 12;
  brick_list.at(4).at(1)->z = 21;

  brick_list.at(4).at(2)->x = 6;
  brick_list.at(4).at(2)->z = 45;

  brick_list.at(4).at(3)->x = 6;
  brick_list.at(4).at(3)->z = 36;

  brick_list.at(4).at(4)->x = 6;
  brick_list.at(4).at(4)->z = 27;
}

void createBricks() {
  float x = 30.0;
  float z = 52.0;
  int i,j;
  vector<Brick*> aux_vec;
  Brick* aux_brick;

  for (i = 0; i < 5; i++) {
    aux_vec.clear();
    for (j = 0; j < 5; j++) {
      aux_brick = new Brick();
      //aux_brick->x = x;
      //aux_brick->z = z;
      aux_brick->red = 0.8;
      aux_brick->matrix_pos.first = i;
      aux_brick->matrix_pos.second = j;
      
      x -= 6.0;
      aux_vec.push_back(aux_brick);
    }

    brick_list.push_back(aux_vec);

    x = 30.0;
    z -= 6.0;
  }

  displayBricks2();
}

//Los bricks verdes son los estaticos
void chooseStaticBricks() {
  int rand_row_val, rand_col_val, i;
  Brick* aux;
   
  for (i = 0; i < 5; i++) {
    rand_row_val = rand() % 5;
    rand_col_val = rand() % 5;
    aux = brick_list.at(rand_row_val).at(rand_col_val);
    aux->type = 1;
    aux->red = 0.196;
    aux->green = 0.803;
    aux->blue = 0.196;
  }
}

void chooseBaseBonusBricks() {
  int rand_row_val, rand_col_val, i;
  Brick* aux;
   
  i = 0;
  while(i < 5) {    
    rand_row_val = rand() % 5;
    rand_col_val = rand() % 5;    
    aux = brick_list.at(rand_row_val).at(rand_col_val);
    
    if (aux->type == 0) {
      aux->bonus.first = 1;
      i++;
    }    
  }
}

void chooseBallBonusBricks() {
  int rand_row_val, rand_col_val, i;
  Brick* aux;
   
  i = 0;
  while(i < 5) {    
    rand_row_val = rand() % 5;
    rand_col_val = rand() % 5;    
    aux = brick_list.at(rand_row_val).at(rand_col_val);
    
    if ((aux->type == 0) && (aux->bonus.first == 0)) {
      aux->bonus.first = 1;
      aux->bonus.second = 1;
      i++;
    }    
  }
}

void hit_bar(Sphere* ball, Base* bar) {
  if (ball->z-ball->radius <= (bar->z)+0.6 && 
      ball->z-ball->radius >= (bar->z)+0.4 && 
      ball->x > (bar->x - bar->longt/2) && 
      ball->x < (bar->x + bar->longt/2))
    ball->hit_bar = 1;
  else
    if (ball->z <= (bar->z)+0.6 && 
	ball->z >= (bar->z)-0.6 && 
	ball->x-ball->radius >= (bar->x + bar->longt/2)-0.4 &&
	ball->x-ball->radius <= (bar->x + bar->longt/2)+0.4)
      ball->hit_bar = 2;
  else 
    if (ball->z <= (bar->z)+0.6 && 
	ball->z >= (bar->z)-0.6 && 
	ball->x+ball->radius <= (bar->x - bar->longt/2)+0.4 &&
	ball->x+ball->radius >= (bar->x - bar->longt/2)-0.4)
      ball->hit_bar = 3;
}

pair<int, int> detectCollisionBrick() {
  vector< vector<Brick*> >::iterator row_it;
  vector<Brick*>::iterator col_it;

  int i, j;
  double dist = sin(45.0*PI/180);

  Brick* left_ray = NULL;
  Brick* middle_ray = NULL;
  Brick* right_ray = NULL;
  
  dist *= ball->radius;
  i = j = 0;
  
  for (row_it = brick_list.begin(); row_it != brick_list.end(); row_it++) {
    for (col_it = (*row_it).begin(); col_it != (*row_it).end(); col_it++) {

      if (ball->u == 1 && ball->l == 1) {
	if (((ball->x + dist + 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist + 2.0 <= (*col_it)->z - 0.4) && 
	     (ball->z - dist + 2.0 >= (*col_it)->z - 0.6)) || 

	    ((ball->x + dist + 2.0 <= (*col_it)->x - 0.9) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist + 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist + 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    left_ray = (*col_it);
	}

	if (((ball->x + dist + 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z - 0.4) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6)) || 

	    ((ball->x + dist + 2.0 <= (*col_it)->x - 0.9) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    middle_ray = (*col_it);
	}

	if (((ball->x - dist + 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z - 0.4) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6)) || 

	    ((ball->x - dist + 2.0 <= (*col_it)->x - 0.9) && 
	     (ball->x - dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    right_ray = (*col_it);
	}
      }
      else if (ball->u == 1 && ball->r == 1) {
	if (((ball->x + dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist - 2.0 >= (*col_it)->x + 0.9) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6)) ||
 
	    ((ball->x + dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist - 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z - 0.4) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    left_ray = (*col_it);
	}

	if (((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x + 0.9) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6)) ||
 
	    ((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist + 2.0 <= (*col_it)->z - 0.4) && 
	     (ball->z + dist + 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    middle_ray = (*col_it);
	}

	if (((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x + 0.9) && 
	     (ball->z - dist + 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist + 2.0 >= (*col_it)->z - 0.6)) ||
 
	    ((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist + 2.0 <= (*col_it)->z - 0.4) && 
	     (ball->z - dist + 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    right_ray = (*col_it);
	}
      }
      else if (ball->d == 1 && ball->l == 1) {
	if (((ball->x + dist + 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist - 2.0 >= (*col_it)->z + 0.4)) ||
	    
	    ((ball->x + dist + 2.0 <= (*col_it)->x - 0.9) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist - 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    left_ray = (*col_it);
	}

	if (((ball->x + dist + 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z + 0.4)) ||
	    
	    ((ball->x + dist + 2.0 <= (*col_it)->x - 0.9) && 
	     (ball->x + dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    middle_ray = (*col_it);
	}

	if (((ball->x - dist + 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z + 0.4)) ||
	    
	    ((ball->x - dist + 2.0 <= (*col_it)->x - 0.9) && 
	     (ball->x - dist + 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    right_ray = (*col_it);
	}
      }
      else if (ball->d == 1 && ball->r == 1) {
	if (((ball->x + dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist - 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z + 0.4)) ||
	    
	    ((ball->x + dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x + dist - 2.0 >= (*col_it)->x + 0.9) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    left_ray = (*col_it);
	}

	if (((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z + 0.4)) ||
	    
	    ((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x + 0.9) && 
	     (ball->z - dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z - dist - 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    middle_ray = (*col_it);
	}

	if (((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x - 1.1) && 
	     (ball->z + dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist - 2.0 >= (*col_it)->z + 0.4)) ||
	    
	    ((ball->x - dist - 2.0 <= (*col_it)->x + 1.1) && 
	     (ball->x - dist - 2.0 >= (*col_it)->x + 0.9) && 
	     (ball->z + dist - 2.0 <= (*col_it)->z + 0.6) && 
	     (ball->z + dist - 2.0 >= (*col_it)->z - 0.6))) {
	  if ((*col_it)->life == 1)
	    right_ray = (*col_it);
	}
      }
      j++;
    }
    i++;
    j = 0;
  }

  if (left_ray == NULL && middle_ray == NULL && right_ray == NULL) {
    return pair<int, int> (-1, -1);
  }
  else if (left_ray != NULL && middle_ray == NULL && right_ray == NULL) {
    return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
  }
  else if (left_ray == NULL && middle_ray != NULL && right_ray == NULL) {
    return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
  }
  else if (left_ray == NULL && middle_ray == NULL && right_ray != NULL) {
    return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
  }
  else if (left_ray != NULL && middle_ray != NULL && right_ray == NULL) {
    if (ball->u == 1 && ball->l == 1) {
      if (sqrt(pow(ball->x + dist + 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist + 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x + dist + 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - middle_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
      }
    }    
    else if(ball->u == 1 && ball->r == 1) {
      if (sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist - 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - middle_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
      }
    }
    else if (ball->d == 1 && ball->l == 1) {
      if (sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist - 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - middle_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
      }
    }
    else if (ball->d == 1 && ball->r == 1) {
      if (sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist - 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - middle_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
      }
    }    
  }
  else if (left_ray != NULL && middle_ray == NULL && right_ray != NULL) {
    if (ball->u == 1 && ball->l == 1) {
      if (sqrt(pow(ball->x + dist + 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist + 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist + 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }    
    else if(ball->u == 1 && ball->r == 1) {
      if (sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist - 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z - dist + 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }
    else if (ball->d == 1 && ball->l == 1) {
      if (sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist + 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }
    else if (ball->d == 1 && ball->r == 1) {
      if (sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - left_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist - 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z + dist - 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }    
  }
  else if (left_ray == NULL && middle_ray != NULL && right_ray != NULL) {
    if (ball->u == 1 && ball->l == 1) {
      if (sqrt(pow(ball->x + dist + 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - middle_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist + 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }    
    else if(ball->u == 1 && ball->r == 1) {
      if (sqrt(pow(ball->x - dist - 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - middle_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist - 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z - dist + 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }
    else if (ball->d == 1 && ball->l == 1) {
      if (sqrt(pow(ball->x + dist + 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - middle_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist + 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }
    else if (ball->d == 1 && ball->r == 1) {
      if (sqrt(pow(ball->x - dist - 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - middle_ray->matrix_pos.second, 2.0)) < sqrt(pow(ball->x - dist - 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z + dist - 3.0 - right_ray->matrix_pos.second, 2.0))) {
	return pair<int, int> (middle_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
      else {
	return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
      }
    }    
  }
  else if (left_ray != NULL && middle_ray != NULL && right_ray != NULL) {
    double left_dist, middle_dist, right_dist;

    if (ball->u == 1 && ball->l == 1) {
      left_dist = sqrt(pow(ball->x + dist + 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist + 3.0 - left_ray->matrix_pos.second, 2.0));
      middle_dist = sqrt(pow(ball->x + dist + 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - middle_ray->matrix_pos.second, 2.0));
      right_dist = sqrt(pow(ball->x - dist + 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - right_ray->matrix_pos.second, 2.0));           
    }
    else if (ball->u == 1 && ball->r == 1) {
      left_dist = sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - left_ray->matrix_pos.second, 2.0));
      middle_dist = sqrt(pow(ball->x - dist - 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z + dist + 3.0 - middle_ray->matrix_pos.second, 2.0));
      right_dist = sqrt(pow(ball->x - dist - 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z - dist + 3.0 - right_ray->matrix_pos.second, 2.0));
    }
    else if (ball->d == 1 && ball->l == 1) {
      left_dist = sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - left_ray->matrix_pos.second, 2.0));
      middle_dist = sqrt(pow(ball->x + dist + 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - middle_ray->matrix_pos.second, 2.0));
      right_dist = sqrt(pow(ball->x - dist + 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - right_ray->matrix_pos.second, 2.0));
    }
    else if (ball->d == 1 && ball->r == 1) {
      left_dist = sqrt(pow(ball->x + dist - 3.0 - left_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - left_ray->matrix_pos.second, 2.0));
      middle_dist = sqrt(pow(ball->x - dist - 3.0 - middle_ray->matrix_pos.first, 2.0) + pow(ball->z - dist - 3.0 - middle_ray->matrix_pos.second, 2.0));
      right_dist = sqrt(pow(ball->x - dist - 3.0 - right_ray->matrix_pos.first, 2.0) + pow(ball->z + dist - 3.0 - right_ray->matrix_pos.second, 2.0));
    }
    
    if (left_dist < middle_dist && left_dist < right_dist) {
      return pair<int, int> (left_ray->matrix_pos.first, left_ray->matrix_pos.second);
    }
    else if (middle_dist < left_dist && middle_dist < right_dist) {
      return pair<int, int> (middle_ray->matrix_pos.first, middle_ray->matrix_pos.second);
    }
    else if (right_dist < left_dist && right_dist < middle_dist) {
      return pair<int, int> (right_ray->matrix_pos.first, right_ray->matrix_pos.second);
    }
  }
} 

void check_hits_bricks() {
  vector< vector<Brick*> >::iterator it1;
  vector<Brick*>::iterator it2;
  int i, j;
  
  if (flag == 0) {
    bricky = detectCollisionBrick();
  }
  if (bricky.first != -1 && bricky.second != -1) {
    flag = 1;
    if (ball->hit_brick(brick_list.at(bricky.first).at(bricky.second)) == 1) {
      flag = 0;
      if (brick_list.at(bricky.first).at(bricky.second)->type == 0) {
	brick_list.at(bricky.first).at(bricky.second)->life = 0;
	win += 1;
      }
      if (brick_list.at(bricky.first).at(bricky.second)->bonus.first == 1) {
	bon[b] = new Bonus(brick_list.at(bricky.first).at(bricky.second));
 	b++;
      }
    }
  }

  pending_timer--;
  if (pending_timer == 0) {
    flag = 0;
    pending_timer = 4500;
  }
}

void display (void) {
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  gluLookAt(camera_x, camera_y, camera_z, 18.0, 0.0, 30.0, 0.0, 1.0, 0.0);
   
  keysFunc();

  hit_bar(ball,bar);
  ball->draw();
  drawBricks();
  bar->draw();
  hit_bar(ball,bar);
  drawWalls();
  drawBackground(36, 60);

  if (ball->lose_timer == 0) {
    ball->move_to();
  }
  else {
    if (ball->lose_timer == 3000) {
      brick_list.clear();
      createBricks();
      chooseStaticBricks();
      chooseBaseBonusBricks();
      chooseBallBonusBricks();
      ball->lose_timer -= 1;
      bar->longt = 6.0;
      bar->x = 18;
      bar->z = 4;
    }
    ball->lose_timer -= 1;
  }

  check_hits_bricks();
  
  int i;
  for(i=0; i<b; i++) {
    if (bon[i]->active == 1) {
      bon[i]->drop();
      bon[i]->draw();
      bon[i]->set_bonus(bar,ball);
    }
  }

  if (win == 20) {
    cout << "Ganaste!, Felicitacion!\n";
    ball->x = 18;
    ball->z = 10;
    ball->speed = 30.0;
    ball->dir.first = ball->x;
    ball->dir.second = ball->z;
    ball->r = 0;
    ball->l = 1;
    ball->u = 1;
    ball->d = 0;
    ball->hit_bar = 0;
    ball->lose_timer = 3000;
    
    srand(time(NULL));
    float num1 = (rand()/(RAND_MAX*0.5));
    pair < float,float > dir2;
    ball->dir.first = 18;
    ball->dir.second = 8;
    dir2.first = normalize(ball->dir).first;
    dir2.second = normalize(ball->dir).second;
    int num2 = floor((rand()/(RAND_MAX*0.5)));
    ball->z = floor((8 + (dir2.second+0.1)*num1)*10) / 10;
    ball->radius = 0.6;
    ball->speed = 30.0;
    if (num2 == 1) {
      ball->x = floor((18 - (dir2.first+0.1)*num1)*10) / 10;
      ball->r = 1;
      ball->l = 0;
    }
    else {
      ball->x = floor((18 + (dir2.first+0.1)*num1)*10) / 10;
      ball->r = 0;
      ball->l = 1;
    }
    ball->u = 1;
    ball->d = 0;
    
    bar->longt = 6.0;
    bar->x = 18;
    bar->z = 4;
    brick_list.clear();
    createBricks();
    chooseStaticBricks();
    chooseBaseBonusBricks();
    chooseBallBonusBricks();
    ball->lose_timer -= 1;
    win = 0;
  }
  
  keysFunc();

  glutSwapBuffers();

}

void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode (GL_MODELVIEW);
} 

int main (int argc, char **argv) {

  srand(time(NULL));
 
  glutInit (&argc, argv);
  createBricks();
  chooseStaticBricks();
  chooseBaseBonusBricks();
  chooseBallBonusBricks();

  initKeys();

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(640, 480);

  //glutInitDisplayMode (GLUT_SINGLE);
  //glutInitWindowSize (500, 500);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Brick3D");

  glShadeModel(GL_SMOOTH);
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyPressed);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  
  initGL(640, 480);
  
  glutMainLoop ();
  return 0;
}
