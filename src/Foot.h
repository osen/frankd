#include "util.h"

#include "glm/glm.hpp"

struct Foot
{
  static SDL_Texture* texture;
  static SDL_Texture* texturel;
  static util::Sound plod;

  int clientId;
  glm::vec2 pos;
  bool pressure;

  bool begunPressure;

  Foot(int id);
  void update();
  void draw();

  void collision(glm::vec2& oldPos);
  //float getOffsetY();
  bool hasPressure();
};
