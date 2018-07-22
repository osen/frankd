#include "Overlay.h"
#include "Monster.h"

#include <GL/glut.h>

SDL_Texture* Overlay::texture;
std::shared_ptr<Overlay> Overlay::inst;
util::Sound Overlay::lightning;

Overlay::Overlay()
{
  target = 1000;
}

void Overlay::draw()
{
  SDL_Rect r = { 0 };
  r.w = glutGet(GLUT_WINDOW_WIDTH);
  r.h = glutGet(GLUT_WINDOW_HEIGHT);

  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
}

void Overlay::update()
{
  if(Monster::inst->getDistance() > target)
  {
    target += 1000;

    lightning.play();
  }
}
