#include "util.h"

#include <vector>

class Player
{
  int id;
  float x;
  float y;
  float frame;
  int direction;
  int moving;

public:
  static util::Spritesheet* ss;
  static std::vector<Player> all;

  Player(int id);
  void update();
  void draw();
};
