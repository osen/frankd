#include "util.h"

#include "glm/glm.hpp"

struct Foot
{
  static SDL_Texture* texture;

  int clientId;
  glm::vec2 pos;
  bool pressure;

  Foot(int id);
  void update();
  void draw();

  void collision(glm::vec2& oldPos);
  //float getOffsetY();
  bool hasPressure();
};
