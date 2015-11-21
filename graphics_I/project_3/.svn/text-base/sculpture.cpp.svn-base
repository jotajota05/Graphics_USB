#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>

#include "sculpture.h"

using namespace std;

Sculpture::Sculpture(float x, float y, float z, float s, float r, bool r_x, bool r_y, bool r_z, const char* filename, float red, float green, float blue) {  
  x_pos = x;
  y_pos = y;
  z_pos = z;
  scale = s;
  rotation = r;
  x_rotate = r_x;
  y_rotate = r_y;
  z_rotate = r_z;
  m = TriMesh::read(filename);
  color[0] = red;
  color[1] = green;
  color[2] = blue;
}

void Sculpture::draw() {
  int j; 

  if (!m)
    exit(1);
  
  m->need_faces();
  m->need_normals();

  glPushMatrix();
  glColor3f(color[0], color[1], color[2]);
  glTranslatef(x_pos, y_pos, z_pos);
  glScalef(scale, scale, scale);  
  glRotatef(rotation, x_rotate, y_rotate, z_rotate);

  for (j = 0; j < m->faces.size(); j++) { 
    glBegin(GL_TRIANGLES);
    glNormal3f( m->normals[m->faces[j][0]][0], m->normals[m->faces[j][0]][1], m->normals[m->faces[j][0]][2]);
    glVertex3f( m->vertices[m->faces[j][0]][0], m->vertices[m->faces[j][0]][1], m->vertices[m->faces[j][0]][2]);
    glNormal3f( m->normals[m->faces[j][1]][0], m->normals[m->faces[j][1]][1], m->normals[m->faces[j][0]][1]);
    glVertex3f( m->vertices[m->faces[j][1]][0], m->vertices[m->faces[j][1]][1], m->vertices[m->faces[j][1]][2]);
    glNormal3f( m->normals[m->faces[j][2]][0], m->normals[m->faces[j][2]][1], m->normals[m->faces[j][2]][2]);
    glVertex3f( m->vertices[m->faces[j][2]][0], m->vertices[m->faces[j][2]][1], m->vertices[m->faces[j][2]][2]);
    glEnd();
  }

  glPopMatrix();
}
