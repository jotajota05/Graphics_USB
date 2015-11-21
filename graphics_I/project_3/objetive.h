#ifndef OBJETIVE
#define OBJETIVE

using namespace std;

class Objetive {
 public:
  float x_pos;
  float y_pos;
  float z_pos;
  float x_scale;
  float y_scale;
  float z_scale;
 public:
  Objetive(float, float, float, float, float, float);
  void draw();
  void move(string);
};

#endif
