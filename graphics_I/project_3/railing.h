#ifndef RAILING
#define RAILING

using namespace std;

class Railing {
 public:
  float x_pos;
  float y_pos;
  float z_pos;
  float x_scale;
  float y_scale;
  float z_scale;
 public:
  Railing(float, float, float, float, float, float);
  void draw();
};

#endif
