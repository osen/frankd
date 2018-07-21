#include "util.h"

#include <vector>

class Apple
{
public:
  static SDL_Texture* texture;
  static std::vector<Apple> all;

  Apple();

  void update();
  void draw();
};
