#include "util.h"

#include "glm/glm.hpp"

struct Hand
{
  static SDL_Texture* texture;
  static SDL_Texture* texturel;
  static util::Sound grab;

  int clientId;
  glm::vec2 pos;

  Hand(int id);
  void update();
  void draw();
};
