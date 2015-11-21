#ifndef SHELF
#define SHELF

using namespace std;

class Shelf {
 public:
  float x_pos;
  float y_pos;
  float z_pos;
  float x_scale;
  float y_scale;
  float z_scale;
  float x_rot;
  float y_rot;;
  float z_rot;
  float rot;

 public:
  Shelf(float, float, float, float, float, float, float, float, float, float);
  void draw();
};

#endif
