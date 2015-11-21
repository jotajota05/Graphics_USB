#ifndef LAMP
#define LAMP

using namespace std;

class Lamp {
 public:
  int num;
  int type;
  int rotation;
  float x;
  float y;
  float z;
  GLfloat light_ambient[4];
  GLfloat light_diffuse[4];
 public:
  Lamp(int num, int t, int rot, float x,float y, float z, float la_x, float la_y, float la_z, float la_ex, float ld_x, float ld_y, float ld_z, float ld_ex);
  void draw();
  void assign_light();
};

#endif
