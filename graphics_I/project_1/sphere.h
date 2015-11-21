#ifndef SPHERE
#define SPHERE

#include "brick.h"

using namespace std;

class Sphere {
 public:
  float x;
  float z;
  float radius;
  float speed;
  pair < float,float > dir;
  bool l,r,u,d;
  int hit_bar;
  int lose_timer;
 public:
  Sphere();
  void draw();
  void move_to();
  bool hit_brick(Brick* bricky);
};

#endif
