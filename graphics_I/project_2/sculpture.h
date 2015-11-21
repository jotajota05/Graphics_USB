#ifndef SCULPTURE
#define SCULPTURE

#include "TriMesh.h"

using namespace std;

class Sculpture {
 public:
  float x_pos;
  float y_pos;
  float z_pos;
  float scale;
  TriMesh *m;
  float rotation;
  bool x_rotate;
  bool y_rotate;
  bool z_rotate;
  float color[3];
 public:
  Sculpture(float, float, float, float, float, bool, bool, bool, const char*, float red, float green, float blue);
  void draw();
};

#endif
