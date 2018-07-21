#include "util.h"

#include <memory>
#include <vector>

struct Background
{
  static std::shared_ptr<Background> inst;
  static std::vector<SDL_Texture*> grounds;
  static std::vector<SDL_Texture*> skys;
  static std::vector<SDL_Texture*> backgrounds;

  void draw();

};
