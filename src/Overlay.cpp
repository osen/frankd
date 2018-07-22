#include "Overlay.h"
#include "Monster.h"

#include <GL/glut.h>

SDL_Texture* Overlay::texture;
SDL_Texture* Overlay::texturel;
std::shared_ptr<Overlay> Overlay::inst;
util::Sound Overlay::lightning;

Overlay::Overlay()
{
  target = 1000;
  timeout = 0;
}

void Overlay::draw()
{
  SDL_Rect r = { 0 };
  r.w = glutGet(GLUT_WINDOW_WIDTH);
  r.h = glutGet(GLUT_WINDOW_HEIGHT);

  if(timeout > 0)
  {
    SDL_RenderCopy(util::sdl_renderer, texturel, NULL, &r);
  }
  else
  {
    SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
  }
}

void Overlay::update()
{
  if(Monster::inst->getDistance() > target)
  {
    target += 1000;

    lightning.play();
    timeout = 1;
  }

  timeout -= util::delta_time;
}
