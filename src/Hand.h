#include "util.h"

#include "glm/glm.hpp"

struct Hand
{
  static SDL_Texture* texture;
  static util::Sound grab;

  int clientId;
  glm::vec2 pos;

  Hand(int id);
  void update();
  void draw();
};
