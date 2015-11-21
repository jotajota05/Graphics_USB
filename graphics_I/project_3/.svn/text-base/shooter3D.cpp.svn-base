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

#include "TriMesh.h"
#include "structure.h"
#include "base.h"
#include "box.h"
#include "rifle.h"
#include "objetive.h"
#include "railing.h"
#include "bullet.h"
#include "lamp.h"
#include "shelf.h"
#include "sculpture.h"

using namespace std;

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

Box* bx = new Box(0,0,80,2,1,1);
Base* b = new Base(52,0,80,2.6,1,1);
Railing* rail = new Railing(10,0,-80,2,1.2,1);
Shelf* s[2] = {
  new Shelf(166, 30, 140, 40, 2, 10, 0, 1, 0, 55),
  new Shelf(4, 30, 44, 40, 2, 10, 0, 1, 0, -55) 
};
Rifle* r = new Rifle(0,0,0,0,0,0);
Lamp* l[6] = {
  new Lamp(0,80, 58, 118),
  new Lamp(1,160, 58, 118),
  new Lamp(2,100, 58, 104),
  new Lamp(3,140, 58, 104),
  new Lamp(4,80, 58, 87),
  new Lamp(5,160, 58, 87) 
};

float x_person = 100.0;
float y_person = 25.0;
float z_person = -100;
float x_rifle = 120;
float y_rifle = 20;
float z_rifle = 140;
float lastx = 512;
float lasty = 384;
                       
int texture[10];
char* paths[10];

vector<Bullet*> bullets;
vector< pair< int, int > > b_collisions;
vector< pair< int, int > > d_collisions;
vector< pair< int, int > > h_collisions;

Objetive* bullseyes_array[5] = {
  new Objetive(65,31,117.5,0.3,0.3,0.3),
  new Objetive(90,31,117.5,0.3,0.3,0.3),
  new Objetive(115,31,117.5,0.3,0.3,0.3),
  new Objetive(140,31,117.5,0.3,0.3,0.3),
  new Objetive(165,31,117.5,0.3,0.3,0.3) };
vector<Objetive*> bullseyes (bullseyes_array, bullseyes_array + sizeof(bullseyes_array) / sizeof(Objetive*));

Objetive* ducks_array[5] = {
  new Objetive(65,21,102.5,0.3,0.3,0.3),
  new Objetive(90,21,102.5,0.3,0.3,0.3),
  new Objetive(115,21,102.5,0.3,0.3,0.3),
  new Objetive(140,21,102.5,0.3,0.3,0.3),
  new Objetive(165,21,102.5,0.3,0.3,0.3)};
vector<Objetive*> ducks (ducks_array, ducks_array + sizeof(ducks_array) / sizeof(Objetive*));

Objetive* humans_array[5] = {
  new Objetive(50,11,87.5,0.3,0.3,0.3),
  new Objetive(75,11,87.5,0.3,0.3,0.3),
  new Objetive(100,11,87.5,0.3,0.3,0.3),
  new Objetive(125,11,87.5,0.3,0.3,0.3),
  new Objetive(150,11,87.5,0.3,0.3,0.3) };
vector<Objetive*> humans (humans_array, humans_array + sizeof(humans_array) / sizeof(Objetive*));

const char *sculpture1 = "modelos/big_spider.ply";
const char *sculpture2 = "modelos/bunny8192.ply";
const char *sculpture3 = "modelos/ship1.ply";
const char *sculpture4 = "modelos/raven.ply";

Sculpture* sculp[4] =  { 
  new Sculpture(-25, 33, -85, 2.0, -90.0, 1, 0, 0, sculpture1, 0.0, 1.0, 0.0),
  new Sculpture(-35, 33, -110, 40.0, 5.0, 1, 0, 0, sculpture2, 1, 0.54, 0.0),
  new Sculpture(-208, 38, -105, 0.01, -90.0, 1, 0, 0, sculpture3,0.2,0.2,0.2),
  new Sculpture(-220, 37.5, -85, 15.0, 180.0, 0, 1, 0, sculpture4, 0.0,0.0,0.0)
};

void drawSculptures() {
  int i;
  glRotatef(180,0,1,0);
  for (i = 0; i < 4; i++) {
    sculp[i]->draw();
  }
  
};

void SceneConfig() { 
  
  GLfloat global_ambient[] = { 0.4, 0.4, 0.4, 0.4 };
  GLfloat DiffuseLight0[] = {0.85, 0.85, 0.85, 0.85}; 
  GLfloat DiffuseLight1[] = { -0.01, -0.01, -0.03, -0.03 };
  GLfloat AmbientLight0[] = {0.0, 0.0, 0.0, 0.0}; 
  GLfloat LightPosition0[] = {0.0, 0.0, 1.0 , 0.0}; 
  GLfloat SpecularLight0[] = {0.85 ,0.85, 0.85, 0.85, }; 

  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glLightfv (GL_LIGHT0, GL_AMBIENT, AmbientLight0); 
  glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight0); 
  glLightfv (GL_LIGHT1, GL_DIFFUSE, DiffuseLight1); 
  glLightfv (GL_LIGHT0, GL_POSITION, LightPosition0); 
  glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

}

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

void mouseMovement(int x, int y) {

  int diffx = -x+lastx;
  int diffy = -y+lasty;
  lastx = x;
  lasty = y;

  x_rifle += (float) diffx;
  y_rifle += (float) diffy;
}

void mouse (int button, int state, int x, int y) {
  
  if ((button == 0) && (state == 1)) {
    double *p1 = (double*)malloc(sizeof(double)*3);
    p1[0] = x_person;
    p1[1] = y_person;
    p1[2] = z_person;

    double *p2 = (double*)malloc(sizeof(double)*3);
    p2[0] = x_rifle;
    p2[1] = y_rifle;
    p2[2] = z_rifle;

    bullets.push_back(new Bullet(p1, p2, 1));
  }
}

void updateDrawBullets() {
  int i;
  for (i = 0; i < bullets.size(); i++) {
    bullets[i]->draw();
    bullets[i]->updateAlfa();
  }
}

int checkCollisionPoints(vector<double> p1, vector<double> p2, vector<double> p3, double r) {
  double a = pow((p2[0] - p1[0]), 2.0) + pow((p2[1] - p1[1]), 2.0) + pow((p2[2] - p1[2]), 2.0);
  double b = 2.0*(   (    (p2[0] - p1[0]) * (p1[0] - p3[0])  ) + (   (p2[1] - p1[1]) * (p1[1] - p3[1])   ) + (   (p2[2] - p1[2]) * (p1[2] - p3[2])   )   );
  double c = pow(p3[0], 2.0) + pow(p3[1], 2.0) + pow(p3[2], 2.0) + pow(p1[0], 2.0) + pow(p1[1], 2.0) + pow(p1[2], 2.0) - (2.0 * ((p3[0] * p1[0]) + (p3[1] * p1[1]) + (p3[2] * p1[2]))) - pow(r, 2.0);

  if (((b * b) - (4.0 * a * c)) > 0.0) {
    return 1;
  }
  else {
    return 0;
  }
  
}

void detectTargetCollision() {
  int it_b;
  int it_o;

  for (it_b = 0; it_b < bullets.size(); it_b++) {
    for (it_o = 0; it_o < bullseyes.size(); it_o++) {
      vector<double> po1;
      po1.push_back(bullets[it_b]->p3[0]);
      po1.push_back(bullets[it_b]->p3[1]);
      po1.push_back(bullets[it_b]->p3[2]);

      vector<double> po2;
      po2.push_back(bullets[it_b]->p4[0]);
      po2.push_back(bullets[it_b]->p4[1]);
      po2.push_back(bullets[it_b]->p4[2]);
      
      vector<double> po3;
      po3.push_back(bullseyes[it_o]->x_pos + 4.5);
      po3.push_back(bullseyes[it_o]->y_pos + 4.5);
      po3.push_back(bullseyes[it_o]->z_pos);
	
      if (checkCollisionPoints(po1, po2, po3, 6.3 ) && bullets[it_b]->p3[2] >= bullseyes[it_o]->z_pos) {
        bullseyes.erase(bullseyes.begin() + it_o);
        bullets.erase(bullets.begin() + it_b);
        break;
      }
      if (po1[2] >= 140 ) { 
        bullets.erase(bullets.begin() + it_b);
        break;
      }
    }
  }

  for (it_b = 0; it_b < bullets.size(); it_b++) {
    for (it_o = 0; it_o < ducks.size(); it_o++) {
      vector<double> po1;
      po1.push_back(bullets[it_b]->p3[0]);
      po1.push_back(bullets[it_b]->p3[1]);
      po1.push_back(bullets[it_b]->p3[2]);

      vector<double> po2;
      po2.push_back(bullets[it_b]->p4[0]);
      po2.push_back(bullets[it_b]->p4[1]);
      po2.push_back(bullets[it_b]->p4[2]);

      vector<double> po3;
      po3.push_back(ducks[it_o]->x_pos + 4.5);
      po3.push_back(ducks[it_o]->y_pos + 4.5);
      po3.push_back(ducks[it_o]->z_pos);

      if (checkCollisionPoints(po1, po2, po3, 6.3) && bullets[it_b]->p3[2] >= ducks[it_o]->z_pos) {
        ducks.erase(ducks.begin() + it_o);
        bullets.erase(bullets.begin() + it_b);
        break;
      }
      if (po1[2] >= 140 ) { 
          bullets.erase(bullets.begin() + it_b);
          break;
      }
    }
  }

  for (it_b = 0; it_b < bullets.size(); it_b++) {
    for (it_o = 0; it_o < humans.size(); it_o++) {
      vector<double> po1;
      po1.push_back(bullets[it_b]->p3[0]);
      po1.push_back(bullets[it_b]->p3[1]);
      po1.push_back(bullets[it_b]->p3[2]);

      vector<double> po2;
      po2.push_back(bullets[it_b]->p4[0]);
      po2.push_back(bullets[it_b]->p4[1]);
      po2.push_back(bullets[it_b]->p4[2]);

      vector<double> po3;
      po3.push_back(humans[it_o]->x_pos + 4.5);
      po3.push_back(humans[it_o]->y_pos + 4.5);
      po3.push_back(humans[it_o]->z_pos);

      if (checkCollisionPoints(po1, po2, po3, 6.3) && bullets[it_b]->p3[2] >= humans[it_o]->z_pos) {
        humans.erase(humans.begin() + it_o);
        bullets.erase(bullets.begin() + it_b);
        break;
      }
      if (po1[2] >= 140 ) {
          bullets.erase(bullets.begin() + it_b);
          break;
      }
    }
  }    
}

void specialKeyPressed(int key, int x, int y) {
    usleep(100);
    switch (key) {    
    
    case GLUT_KEY_LEFT:
      if (x_person <= 212 ) 
        x_person += 1.5f;
	break;
    
    case GLUT_KEY_RIGHT:
      if (x_person >= 4) x_person -= 1.5f;
	break;

    default:
      printf ("Special key %d pressed. No action there yet.\n", key);
      break;
    }	
}

int ImageLoad(char* filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
	printf("File Not Found : %s\n",filename);
	return 0;
    }    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }
    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);
    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }
    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
    // we're done.
    return 1;
}
    
// Load Bitmaps And Convert To Textures
void LoadGLTextures(char* paths[10]) {	
  int i;
  for (i = 0;i < 10;i++) {  
    // Load Texture
    Image *image1;

    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
      printf("Error allocating space for image");
      exit(0);
    }
    if (!ImageLoad((char *)paths[i], image1)) {
      exit(1);
    }        
    // Create Texture	
    glGenTextures(1,(GLuint*)&texture[i]);
    glBindTexture(GL_TEXTURE_2D, texture[i]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
  }

}

void drawGround() {
  glEnable(GL_TEXTURE_2D);

  Structure* ground;
  ground = new Structure(-100.0, -0.1, -100.0, 400.0, 0.0, 400.0, 0, 0, 0, 0.0 ,0);
  ground->draw();

  glDisable(GL_TEXTURE_2D);
  
}

void initGL(float width, float height) {		       
  paths[0] = (char*)"./textures/wall_texture1.bmp";
  paths[1] = (char*)"./textures/base.bmp";
  paths[2] = (char*)"./textures/bullseye.bmp";
  paths[3] = (char*)"./textures/duck.bmp";
  paths[4] = (char*)"./textures/human.bmp";
  paths[5] = (char*)"./textures/rail.bmp";
  paths[6] = (char*)"./textures/road.bmp";
  paths[7] = (char*)"./textures/walls.bmp";
  paths[8] = (char*)"./textures/graf.bmp";
  paths[9] = (char*)"./textures/graf2.bmp";
 LoadGLTextures(paths);				// Load The Texture(s) 
  glClearColor(0.0, 0.0, 0.0, 0.5);
  glClearDepth(1);
  glDepthFunc(GL_LESS);		
  glEnable(GL_DEPTH_TEST);		

  glShadeModel(GL_SMOOTH);	        
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();			
  gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0);
  glMatrixMode(GL_MODELVIEW);

  }

void display (void) {

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  gluLookAt(x_person, y_person, z_person, x_rifle, y_rifle, z_rifle, 0.0, 1.0, 0.0);
  
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

  glColor3f(0.12,0.12,0.12);

  //ejes();

  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  //glColor3f(0.54,0.14,0.0);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  drawGround();

  glPushMatrix();

  glTranslatef(-5,0,0);

  //glColor3f(0.5,0.5,0.5);
  //  glBindTexture(GL_TEXTURE_2D, texture[0]);
  bx->draw(texture);

  glPopMatrix();

  //glColor3f(0.54,0.0,0.0);
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  rail->draw();

  //glColor3f(0.54,0.6,0.0);
  r->draw();

  //glColor3f(0.0,0.14,0.0);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  b->draw();

  //glColor3f(0.54,0.14,0.2);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  int o = 0;
  
  for (o = 0; o < bullseyes.size(); o++) {
    bullseyes[o]->draw();
    bullseyes[o]->move("R");
  }

  glBindTexture(GL_TEXTURE_2D, texture[3]);
  for (o = 0; o < ducks.size(); o++) {
    ducks[o]->draw();
    ducks[o]->move("L");
  }

  glBindTexture(GL_TEXTURE_2D, texture[4]);
  for (o = 0; o < humans.size(); o++) {
    humans[o]->draw();
    humans[o]->move("R");
  }
 
  updateDrawBullets();
  detectTargetCollision();

  int i = 0;
  for (i=0; i < 6; i++) {
    l[i]->draw();
    l[i]->assign_light();
  }

  glBindTexture(GL_TEXTURE_2D, texture[7]);
  for (i=0; i < 2; i++) {
    s[i]->draw();
  }

  glColor3f(1,1,1);
  drawSculptures();

  glutSwapBuffers();

}

void reshape (int w, int h) {
  if (h==0)  h=1;
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);
  glMatrixMode (GL_MODELVIEW);
} 

int main (int argc, char **argv) {

  glutInit (&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(1024,768);
  glutInitWindowPosition (0,0);
  glutCreateWindow ("Shooter3D - Valdes - Garcia");

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  initGL(1024,768);
  SceneConfig();

  glutSpecialFunc(&specialKeyPressed);
  glutPassiveMotionFunc(mouseMovement); 
  glutMouseFunc(mouse); 

  glutMainLoop ();

  return 0;
}
