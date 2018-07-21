#include "util.h"
#include "glm/glm.hpp"

#include <vector>

class Mob
{
public:
  static SDL_Texture* texture;
  static std::shared_ptr<Mob> inst;

  glm::vec3 pos;

  Mob();

  void update();
  void draw();
};
