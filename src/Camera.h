#include "util.h"
#include "glm/glm.hpp"

#include <vector>
#include <memory>

struct Camera
{
  static std::shared_ptr<Camera> inst;

  glm::vec2 pos;

  Camera();
  void draw();
  glm::vec2 getOffset();

};
