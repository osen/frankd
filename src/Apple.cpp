#include "Apple.h"

SDL_Texture* Apple::texture;
std::vector<Apple> Apple::all;

Apple::Apple()
{

}

void Apple::draw()
{
  SDL_Rect r = { 0 };
  r.x = 200;
  r.y = 200;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
}
