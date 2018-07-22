#include "util.h"

#include <memory>

struct Overlay
{
  static std::shared_ptr<Overlay> inst;
  static SDL_Texture* texture;
  static SDL_Texture* texturel;
  static util::Sound lightning;

  float target;
  float timeout;

  Overlay();
  void update();
  void draw();
};
