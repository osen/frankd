#include "Mob.h"
#include "Camera.h"

SDL_Texture* Mob::texture;
std::shared_ptr<Mob> Mob::inst;

Mob::Mob()
{
  pos.x = -200;
  pos.y = 100;
}

void Mob::draw()
{
  glm::vec2 offset = Camera::inst->getOffset();

  SDL_Rect r = { 0 };
  r.x = pos.x + offset.x;
  r.y = pos.y + offset.y;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
}

void Mob::update()
{
  pos.x += 10 * util::delta_time;
}
