#include "util.h"
#include "glm/glm.hpp"

#include <vector>

class Mob
{
public:
  static SDL_Texture* texture;
  static std::shared_ptr<Mob> inst;

  glm::vec3 pos;
  float speed;
  bool unleashed;

  Mob();

  void unleash();
  bool wasUnleashed();

  void update();
  void draw();
};
