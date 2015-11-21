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
#include "lamp.h"
#include "structure.h"
#include "sculpture.h"
#include "plant.h"

using namespace std;

GLfloat yrot = 230;            
GLfloat walkbias = 30;
GLfloat walkbiasangle = 0;
GLfloat lookupdown = 0.0;
const float piover180 = 0.0174532925f;
float xpos = -80, zpos = -60;
GLfloat z=0.0f;                       

int texture[9];
char* paths[9];

bool light = 0;
GLfloat Sun_LightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat Sun_LightDiffuse[] = { 0.5f, 5.5f, 0.5f, 1.0f };
GLfloat Sun_LightPosition[] = { 20.0f, 25.0f, 20.0f, 1.0f };

const char *sculpture1 = "modelos/big_spider.ply";
const char *sculpture2 = "modelos/bunny8192.ply";
const char *sculpture3 = "modelos/armadillo1024.ply";
const char *sculpture4 = "modelos/ship1.ply";
const char *sculpture5 = "modelos/raven.ply";
const char *sculpture6 = "modelos/snail.ply";
int num_sculp = 6;
Sculpture* sculptures[6];

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

typedef struct Image Image;

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

int ImageLoad(char* filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
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
void LoadGLTextures(char* paths[9]) {	
  int i;
  for (i = 0;i < 9;i++) {  
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

void initGL(float width, float height) {		       
  paths[0] = (char*)"./textures/wall_texture10.bmp";
  paths[1] = (char*)"./textures/floor_texture3.bmp";
  paths[2] = (char*)"./textures/ground_texture.bmp";
  paths[3] = (char*)"./textures/sky_texture5.bmp";
  paths[4] = (char*)"./textures/plant_texture.bmp";
  paths[5] = (char*)"./textures/gorilla.bmp";
  paths[6] = (char*)"./textures/birds.bmp";
  paths[7] = (char*)"./textures/giraffe.bmp";
  paths[8] = (char*)"./textures/elephant.bmp";
  LoadGLTextures(paths);				// Load The Texture(s) 
  glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
  glClearColor(0.0, 0.0, 0.0, 0.5);
  glClearDepth(1);
  glDepthFunc(GL_LESS);		
  glEnable(GL_DEPTH_TEST);		

  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT0, GL_AMBIENT, Sun_LightAmbient);  
  glLightfv(GL_LIGHT0, GL_DIFFUSE, Sun_LightDiffuse);  
  glLightfv(GL_LIGHT0, GL_POSITION, Sun_LightPosition); 
  glEnable(GL_LIGHT0);

  glShadeModel(GL_SMOOTH);	        
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();			
  gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0);
  glMatrixMode(GL_MODELVIEW);

  }

void keyPressed(unsigned char key, int x, int y) {
    usleep(100);

    switch (key) {    
    case 'l': 
    case 'L': // switch the lighting
	printf("L/l pressed; lighting is: %d\n", light);
	light = light ? 0 : 1;              // switch the current value of light, between 0 and 1.
	if (light) {
	    glEnable(GL_LIGHTING);
	} else {
	    glDisable(GL_LIGHTING);
	}
	printf("Lighting is now: %d\n", light);
	break;

    default:
      printf ("Key %d pressed. No action there yet.\n", key);
      break;
    }	
}


void specialKeyPressed(int key, int x, int y) {
    usleep(100);

    switch (key) {    
    case GLUT_KEY_PAGE_UP:
	z -= 0.2f;
	lookupdown -= 1.0f;
    if (lookupdown == -360) lookupdown = 0;
	break;
    
    case GLUT_KEY_PAGE_DOWN:
	z += 0.2f;
	lookupdown += 1.0f;
    if (lookupdown == 360) lookupdown = 0;
	break;

    case GLUT_KEY_UP:
	xpos -= (float)sin(yrot*piover180) * 2.0f;
	zpos -= (float)cos(yrot*piover180) * 2.05f;	
    if (lookupdown < 0)
      walkbias -= (float)sin(lookupdown * piover180)*2.0f;
    else walkbias -= (float)sin(lookupdown * piover180)*2.0f;
	break;

    case GLUT_KEY_DOWN:
	xpos += (float)sin(yrot*piover180) * 2.0f;
	zpos += (float)cos(yrot*piover180) * 2.0f;	
    if (lookupdown > 0)
      walkbias += (float)sin(lookupdown * piover180)*2.0f;
    else walkbias += (float)sin(lookupdown * piover180)*2.0f;
	break;

    case GLUT_KEY_LEFT:
	yrot += 1.5f;
	break;
    
    case GLUT_KEY_RIGHT:
	yrot -= 1.5f;
	break;

    default:
      printf ("Special key %d pressed. No action there yet.\n", key);
      break;
    }	
}

void drawFrame(float x, float y, float z, float sx, float sy, float sz, float rot1, float rot2) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(sx, sy, sz);
  glRotatef(rot1, 0.0, 0.0, 1.0);
  glRotatef(rot2, 1.0, 0.0, 0.0);
  glColor3f(0.54,0.14,0.0);
  
  //Base
  glBegin(GL_QUADS);
  glVertex3f(2.0,0.0,2.5);
  glVertex3f(-2.0,0.0,2.5);
  glVertex3f(-2.0,0.0,-2.5);
  glVertex3f(2.0,0.0,-2.5);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,1.0);
  glVertex3f(2.0,0.0,2.5);
  glVertex3f(2.0,0.3,2.5);
  glVertex3f(-2.0,0.3,2.5);
  glVertex3f(-2.0,0.0,2.5);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(1.0,0.0,0.0);
  glVertex3f(2.0,0.0,2.5);
  glVertex3f(2.0,0.3,2.5);
  glVertex3f(2.0,0.3,-2.5);
  glVertex3f(2.0,0.0,-2.5);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,-1.0);
  glVertex3f(2.0,0.0,-2.5);
  glVertex3f(2.0,0.3,-2.5);
  glVertex3f(-2.0,0.3,-2.5);
  glVertex3f(-2.0,0.0,-2.5);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glVertex3f(-2.0,0.0,2.5);
  glVertex3f(-2.0,0.3,2.5);
  glVertex3f(-2.0,0.3,-2.5);
  glVertex3f(-2.0,0.0,-2.5);
  glEnd();

  glColor3f(0.8,0.52,0.35);
  //Marco
  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glVertex3f(2.0,0.3,2.5);
  glVertex3f(1.3,0.15,1.8);
  glVertex3f(-1.3,0.15,1.8);
  glVertex3f(-2.0,0.3,2.5);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glVertex3f(2.0,0.3,2.5);
  glVertex3f(1.3,0.15,1.8);
  glVertex3f(1.3,0.15,-1.8);
  glVertex3f(2.0,0.3,-2.5);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glVertex3f(2.0,0.3,-2.5);
  glVertex3f(1.3,0.15,-1.8);
  glVertex3f(-1.3,0.15,-1.8);
  glVertex3f(-2.0,0.3,-2.5);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glVertex3f(-2.0,0.3,2.5);
  glVertex3f(-1.3,0.15,1.8);
  glVertex3f(-1.3,0.15,-1.8);
  glVertex3f(-2.0,0.3,-2.5);
  glEnd();

  glEnable(GL_TEXTURE_2D);
  glColor3f(0.87,0.72,0.53);
  //Foto
  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glTexCoord2f(0.0,1.0);glVertex3f(-1.3,0.15,1.8);
  glTexCoord2f(0.0,0.0);glVertex3f(-1.3,0.15,-1.8);
  glTexCoord2f(1.0,0.0);glVertex3f(1.3,0.15,-1.8);
  glTexCoord2f(1.0,1.0);glVertex3f(1.3,0.15,1.8);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  glPopMatrix();
}

void drawBustBase(float x, float y, float z, float sx, float sy, float sz) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(sx, sy, sz);
  glColor3f(0.54,0.14,0.0);
  
  //Base de abajo
  glBegin(GL_QUADS);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(-1.0,0.0,1.0);
  glVertex3f(-1.0,0.0,-1.0);
  glVertex3f(1.0,0.0,-1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glVertex3f(-1.0,0.0,-1.0);
  glVertex3f(-0.8,0.3,-0.8);
  glVertex3f(-0.8,0.3,0.8);
  glVertex3f(-1.0,0.0,1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(1.0,0.0,0.0);
  glVertex3f(1.0,0.0,-1.0);
  glVertex3f(0.8,0.3,-0.8);
  glVertex3f(0.8,0.3,0.8);
  glVertex3f(1.0,0.0,1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,-1.0);
  glVertex3f(-1.0,0.0,-1.0);
  glVertex3f(-0.8,0.3,-0.8);
  glVertex3f(0.8,0.3,-0.8);
  glVertex3f(1.0,0.0,-1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,1.0);
  glVertex3f(-1.0,0.0,1.0);
  glVertex3f(-0.8,0.3,0.8);
  glVertex3f(0.8,0.3,0.8);
  glVertex3f(1.0,0.0,1.0);
  glEnd();

  //Tranco de la base
  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glVertex3f(-0.8,0.3,0.8);
  glVertex3f(-0.8,0.3,-0.8);
  glVertex3f(-0.8,2.3,-0.8);
  glVertex3f(-0.8,2.3,0.8);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(1.0,0.0,0.0);
  glVertex3f(0.8,0.3,-0.8);
  glVertex3f(0.8,0.3,0.8);
  glVertex3f(0.8,2.3,0.8);
  glVertex3f(0.8,2.3,-0.8);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,-1.0);
  glVertex3f(-0.8,0.3,-0.8);
  glVertex3f(0.8,0.3,-0.8);
  glVertex3f(0.8,2.3,-0.8);
  glVertex3f(-0.8,2.3,-0.8);
  glEnd();
  
  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,1.0);
  glVertex3f(-0.8,0.3,0.8);
  glVertex3f(0.8,0.3,0.8);
  glVertex3f(0.8,2.3,0.8);
  glVertex3f(-0.8,2.3,0.8);
  glEnd();

  //Base de arriba
  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glVertex3f(-0.8,2.3,-0.8);
  glVertex3f(-0.8,2.3,0.8);
  glVertex3f(-1.2,2.6,1.2);
  glVertex3f(-1.2,2.6,-1.2);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(1.0,0.0,0.0);
  glVertex3f(0.8,2.3,-0.8);
  glVertex3f(0.8,2.3,0.8);
  glVertex3f(1.2,2.6,1.2);
  glVertex3f(1.2,2.6,-1.2);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,-1.0);
  glVertex3f(-0.8,2.3,-0.8);
  glVertex3f(0.8,2.3,-0.8);
  glVertex3f(1.2,2.6,-1.2);
  glVertex3f(-1.2,2.6,-1.2);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,1.0);
  glVertex3f(0.8,2.3,0.8);
  glVertex3f(-0.8,2.3,0.8);
  glVertex3f(-1.2,2.6,1.2);
  glVertex3f(1.2,2.6,1.2);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glVertex3f(1.2,2.6,1.2);
  glVertex3f(1.2,2.6,-1.2);
  glVertex3f(-1.2,2.6,-1.2);
  glVertex3f(-1.2,2.6,1.2);
  glEnd();
  
  glPopMatrix();
}

void drawFlatBase(float x, float y, float z, float sx, float sy, float sz) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(sx, sy, sz);
  glColor3f(0.54,0.14,0.0);
  
  //Base de abajo
  glBegin(GL_QUADS);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(-1.0,0.0,1.0);
  glVertex3f(-1.0,0.0,-1.0);
  glVertex3f(1.0,0.0,-1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(-1.0,0.0,0.0);
  glVertex3f(-1.0,0.0,-1.0);
  glVertex3f(-0.8,0.3,-0.8);
  glVertex3f(-0.8,0.3,0.8);
  glVertex3f(-1.0,0.0,1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(1.0,0.0,0.0);
  glVertex3f(1.0,0.0,-1.0);
  glVertex3f(0.8,0.3,-0.8);
  glVertex3f(0.8,0.3,0.8);
  glVertex3f(1.0,0.0,1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,-1.0);
  glVertex3f(-1.0,0.0,-1.0);
  glVertex3f(-0.8,0.3,-0.8);
  glVertex3f(0.8,0.3,-0.8);
  glVertex3f(1.0,0.0,-1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,1.0);
  glVertex3f(-1.0,0.0,1.0);
  glVertex3f(-0.8,0.3,0.8);
  glVertex3f(0.8,0.3,0.8);
  glVertex3f(1.0,0.0,1.0);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0.0,1.0,0.0);
  glVertex3f(-0.8,0.3,0.8);
  glVertex3f(0.8,0.3,0.8);
  glVertex3f(0.8,0.3,-0.8);
  glVertex3f(-0.8,0.3,-0.8);
  glEnd();

  glPopMatrix();
}

void loadSculptures() {
  //Esculturas de 1er piso
  sculptures[0] = new Sculpture(21.5, 27.9, 58.0, 1.0, -90.0, 1, 0, 0, sculpture1, 0.1, 0.1, 0.1);
  sculptures[1] = new Sculpture(40.0, 27.75, 24.5, 21.0, 5.0, 1, 0, 0, sculpture2, 0.8, 0.52, 0.25);
  sculptures[2] = new Sculpture(55.0, 27.75, 52.0, 0.01, -90.0, 1, 0, 0, sculpture4,0.0,0.0,0.2);
  //Esculturas de PB
  sculptures[3] = new Sculpture(25.5, 3.8, 55, 15.0, 180.0, 0, 1, 0, sculpture5, 0.2, 0.2, 0.2);
  sculptures[4] = new Sculpture(25.0, 3.5, 25.0, 0.06, 0.0, 0, 1, 0, sculpture3, 0.1, 0.1, 0.1);
  sculptures[5] = new Sculpture(51.5, 4.4, 43.0, 1.0, -90.0, 1, 0, 0, sculpture1, 0.1, 0.1, 0.1);
}

void drawSculptures() {
  int i;

  for (i = 0; i < num_sculp; i++) {
    sculptures[i]->draw();
  }
  
}

void drawWalls() {

glEnable(GL_TEXTURE_2D);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glBindTexture(GL_TEXTURE_2D, texture[0]);

  int i = 0;
  Structure* wall1[5];
  wall1[0] = new Structure(10.0, 22.0, 0.99, 10.0, 22.0, 1.0, 0, 0, 0, 0.0 ,"front");
  wall1[1] = new Structure(70.0, 22.0, 0.99, 10.0, 22.0, 1.0, 0, 0, 0, 0.0 ,"front");
  wall1[2] = new Structure(40.0, 5.0, 0.99, 20.0, 5.0, 1.0, 0, 0, 0, 0.0 ,"front");  
  wall1[3] = new Structure(40.0, 24, 0.99, 20.0, 8.0, 1.0, 0, 0, 0, 0.0 ,"front");  
  wall1[4] = new Structure(40.0, 41.0, 0.99, 20.0, 3.0, 1.0, 0, 0, 0, 0.0 ,"front");
  for (i = 0;i < 5;i++)
    wall1[i]->draw();
  Structure* wall2[5];
  wall2[0] = new Structure(0.99, 22.0, 10.0, 1.0, 22.0, 10.0, 0, 0, 0, 0.0 ,"rear");
  wall2[1] = new Structure(0.99, 22.0, 70.0, 1.0, 22.0, 10.0, 0, 0, 0, 0.0 ,"rear");
  wall2[2] = new Structure(0.99, 5.0, 40.0, 1.0, 5.0, 20.0, 0, 0, 0, 0.0 ,"rear");  
  wall2[3] = new Structure(0.99, 24, 40.0, 1.0, 8.0, 20.0, 0, 0, 0, 0.0 ,"rear");  
  wall2[4] = new Structure(0.99, 41.0, 40.0, 1.0, 3.0, 20.0, 0, 0, 0, 0.0 ,"rear");
  for (i = 0;i < 5;i++)
    wall2[i]->draw();
  Structure* wall3[5];
  wall3[0] = new Structure(10.0, 22.0, 79.01, 10.0, 22.0, 1.0, 0, 0, 0, 0.0 ,"front");
  wall3[1] = new Structure(70.0, 22.0, 79.01, 10.0, 22.0, 1.0, 0, 0, 0, 0.0 ,"front");
  wall3[2] = new Structure(40.0, 5.0, 79.01, 20.0, 5.0, 1.0, 0, 0, 0, 0.0 ,"front");  
  wall3[3] = new Structure(40.0, 24.0, 79.01, 20.0, 8.0, 1.0, 0, 0, 0, 0.0 ,"front");  
  wall3[4] = new Structure(40.0, 41.0, 79.01, 20.0, 3.0, 1.0, 0, 0, 0, 0.0 ,"front");
  for (i = 0;i < 5;i++)
    wall3[i]->draw();
  Structure* wall4[5];
  wall4[0] = new Structure(79.01, 22.0, 10.0, 1.0, 22.0, 10.0, 0, 0, 0, 0.0 ,"rear");
  wall4[1] = new Structure(79.01, 22.0, 70.0, 1.0, 22.0, 10.0, 0, 0, 0, 0.0 ,"rear");
  wall4[2] = new Structure(79.01, 5.0, 40.0, 1.0, 5.0, 20.0, 0, 0, 0, 0.0 ,"rear");  
  wall4[3] = new Structure(79.01, 24, 40.0, 1.0, 8.0, 20.0, 0, 0, 0, 0.0 ,"rear");  
  wall4[4] = new Structure(79.01, 41.0, 40.0, 1.0, 3.0, 20.0, 0, 0, 0, 0.0 ,"rear");
  for (i = 0;i < 5;i++)
    wall4[i]->draw();

  glDisable(GL_TEXTURE_2D);

}

void drawLamps() {
  Lamp* l1 = new Lamp(1, 1, 90, 40, 18.75, 2, 0.1f, 0.1f, 0.1f, 1.0f, 0.3f, 0.3f, 0.3f, 1.0f);
  l1->draw();
  Lamp* l2 = new Lamp(2, 1, 90, 40, 40, 2, 0.1f, 0.1f, 0.1f, 1.0f, 0.3f, 0.3f, 0.3f, 1.0f);
  l2->draw();
  Lamp* l3 = new Lamp(3, 1, 270, 40, 18.75, 78, 0.1f, 0.1f, 0.1f, 1.0f, 0.3f, 0.3f, 0.3f, 1.0f);
  l3->draw();
  Lamp* l4 = new Lamp(4, 1, 270, 40, 40, 78, 0.1f, 0.1f, 0.1f, 1.0f, 0.3f, 0.3f, 0.3f, 1.0f);
  l4->draw();
  Lamp* l5 = new Lamp(5, 0, 0, 70, 23.5, 70, 0.1f, 0.1f, 0.1f, 1.0f, 0.3f, 0.3f, 0.3f, 1.0f);
  l5->draw();
  Lamp* l6 = new Lamp(6, 0, 0, 10, 0, 10, 0.1f, 0.1f, 0.1f, 1.0f, 0.3f, 0.3f, 0.3f, 1.0f);
  l6->draw();
}
void drawPlants() {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[4]);

  Plant* p1 = new Plant(10,33.5,10,3,6,0.01);
  p1->draw();
  Plant* p2 = new Plant(70,10.0,70,3,6,0.01);
  p2->draw();

  glDisable(GL_TEXTURE_2D);
}

void drawRoof() {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  
  Structure* roof[2];
  roof[0] = new Structure(40.0, 45.0, 40.0, 50.0, 1.0, 50.0, 0, 0, 0, 0.0 ,"roof");
  roof[0]->draw();
  roof[1] = new Structure(40.0, 23, 40.0, 40.0, 0.0, 40.0, 0, 0, 0, 0.0 ,"roof");
  roof[1]->draw();

  glDisable(GL_TEXTURE_2D);
}

void drawFloors() {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  
  Structure* floor[2];
  floor[0] = new Structure(40.0, 0.0, 40.0, 40.0, 0.0, 40.0, 0, 0, 0, 0.0 ,"floor");
  floor[1] = new Structure(40.0, 23.3, 40.0, 40.0, 0.0, 40.0, 0, 0, 0, 0.0 ,"floor");
  glColor3f(0,0,1);
  floor[0]->draw();
  glColor3f(0,1,0);
  floor[1]->draw();

  glDisable(GL_TEXTURE_2D);
}

void drawGround() {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[2]);

  Structure* ground;
  ground = new Structure(0.0, -0.1, 0.0, 200.0, 0.0, 200.0, 0, 0, 0, 0.0 ,"ground");
  ground->draw();

  glDisable(GL_TEXTURE_2D);
  
}

void drawSky() {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[3]);

  Structure* sky[5];
  sky[0] = new Structure(200.0, 100.0, 0.0, 0.0, 100.0, 200.0, 0, 0, 0, 0.0 ,"sky");
  sky[0]->draw();
  sky[1] = new Structure(-200.0, 100.0, 0.0, 0.0, 100.0, 200.0, 0, 0, 0, 0.0 ,"sky");
  sky[1]->draw();
  sky[2] = new Structure(0.0, 100.0, 200.0, 200.0, 100.0, 0.0, 0, 0, 0, 0.0 ,"sky");
  sky[2]->draw();
  sky[3] = new Structure(0.0, 100.0, -200.0, 200.0, 100.0, 0.0, 0, 0, 0, 0.0 ,"sky");
  sky[3]->draw();
  sky[4] = new Structure(0.0, 100.0, 0.0, 200.0, 0.0, 200.0, 0, 0, 0, 0.0 ,"sky");
  sky[4]->draw();

  glDisable(GL_TEXTURE_2D);
  
}

void display (void) {
  
  GLfloat xtrans, ztrans, ytrans;
  GLfloat sceneroty;
  
  // calculate translations and rotations.
  xtrans = -xpos;
  ztrans = -zpos;
  ytrans = -walkbias-0.25f;
  sceneroty = 360.0f - yrot;
    	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  glRotatef(lookupdown, 1.0f, 0, 0);
  glRotatef(sceneroty, 0, 1.0f, 0);
  
  glTranslatef(xtrans, ytrans, ztrans);    

  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //ejes();

  drawWalls();
  drawFloors();
  drawGround();
  drawSky();
  drawRoof();
  drawLamps();
  drawPlants();

  //Bases del 1er Piso
  drawBustBase(25.0, 23.5, 55.0, 1.9, 1.9, 1.9);
  drawBustBase(40.0, 23.5, 25.0, 1.9, 1.9, 1.9);
  drawFlatBase(55.0, 23.5, 55.0, 3.5, 1.0, 3.5);

  //Bases de PB
  drawFlatBase(25.0, 0.0, 55.0, 3.5, 1.2, 3.5);
  drawFlatBase(25.5, 0.0, 25.0, 4, 1.2, 4);
  drawBustBase(55.0, 0.0, 40.0, 1.9, 1.9, 1.9);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  drawFrame(11, 12.0, 78, 2, 2, 2, 0, -90);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  drawFrame(77, 12.0, 11, 2, 2, 2, 90, 0);
  glBindTexture(GL_TEXTURE_2D, texture[7]);
  drawFrame(77, 33.0, 11, 2, 2, 2, 90, 0);
  glBindTexture(GL_TEXTURE_2D, texture[8]);
  drawFrame(11, 33.0, 78, 2, 2, 2, 90, -90);

  loadSculptures();
  drawSculptures();

  glutSwapBuffers();

}

void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);
  glMatrixMode (GL_MODELVIEW);
} 

int main (int argc, char **argv) {

  srand(time(NULL));
 
  glutInit (&argc, argv);
  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(1024,768);

  glutInitWindowPosition (0,0);
  glutCreateWindow ("Museum 3D - Valdes - Garcia");

  glShadeModel(GL_SMOOTH);
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  glutKeyboardFunc(&keyPressed);
  glutSpecialFunc(&specialKeyPressed);
  
  initGL(1024,768);
  
  glutMainLoop ();
  return 0;
}
