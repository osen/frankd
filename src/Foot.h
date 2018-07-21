#include "util.h"

struct Foot
{
  static SDL_Texture* texture;

  int clientId;
  util::Vec2 pos;

  Foot(int id);
  void update();
  void draw();

  void collision(util::Vec2& oldPos);
};
