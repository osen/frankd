#include "util.h"

#include <memory>

struct Overlay
{
  static std::shared_ptr<Overlay> inst;
  static SDL_Texture* texture;
  static util::Sound lightning;

  float target;

  Overlay();
  void update();
  void draw();
};
