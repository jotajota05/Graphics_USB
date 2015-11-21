#ifndef BASE
#define BASE

using namespace std;

class Base {
 public:
  float x_pos;
  float y_pos;
  float z_pos;
  float x_scale;
  float y_scale;
  float z_scale;
 public:
  Base(float, float, float, float, float, float);
  void draw();
};

#endif
