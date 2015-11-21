#ifndef RIFLE
#define RIFLE

using namespace std;

class Rifle {
 public:
  float x_pos;
  float y_pos;
  float z_pos;
  float x_scale;
  float y_scale;
  float z_scale;
 public:
  Rifle(float, float, float, float, float, float);
  void draw();
};

#endif
