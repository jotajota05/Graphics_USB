#ifndef LAMP
#define LAMP

using namespace std;

class Lamp {
 public:
  int num;
  float x;
  float y;
  float z;
 public:
  Lamp(int num,  float x, float y, float z);
  void draw();
  void assign_light();
};

#endif
