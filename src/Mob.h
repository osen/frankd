#include "util.h"
#include "glm/glm.hpp"

#include <vector>

class Mob
{
public:
  static SDL_Texture* texture;
  static std::shared_ptr<Mob> inst;
  static std::vector<util::Sound> shouts;

  glm::vec3 pos;
  float speed;
  bool unleashed;
  float shoutTimer;

  Mob();

  void unleash();
  bool wasUnleashed();
  bool hasCaught();

  void update();
  void draw();
};
