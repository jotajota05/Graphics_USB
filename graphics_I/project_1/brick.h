#ifndef BRICK
#define BRICK

#include <vector>

using namespace std;

/*
 * type = 0 El bloque NO es estatico
 * type = 1 El bloque es estatico
 * 
 * bonus.first = 0 El bloque NO tiene bonus.
 * bonus.first = 1 El bloque tiene bonus.
 * bonus.second = 0 El bloque tiene bonus que agranda la base.
 * bonus.second = 1 El bloque tiene bonus que aumenta la velocidad de la pelota.
 */
class Brick {
 public:
  float x;
  float z;
  bool life;
  pair < bool, bool > bonus;
  bool type;
  float red;
  float green;
  float blue;
  pair<int, int> matrix_pos;
 public:
  Brick();
  void draw();
  void drop_bonus();
  int equal(Brick*);
  int compare(vector<Brick*>);
};

#endif


