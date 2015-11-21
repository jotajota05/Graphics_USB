#ifndef PLANT
#define PLANT

using namespace std;

class Plant {
 public:
  float x_pos;
  float y_pos;
  float z_pos;
  float x_scale;
  float y_scale;
  float z_scale;
 public:
  Plant(float, float, float, float, float, float);
  void draw();
};

#endif
