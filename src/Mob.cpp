#include "Mob.h"
#include "Camera.h"
#include "Monster.h"

#include <iostream>

SDL_Texture* Mob::texture;
std::shared_ptr<Mob> Mob::inst;
std::vector<util::Sound> Mob::shouts;

Mob::Mob()
{
  pos.x = -300;
  pos.y = 100;
  speed = 10;
  unleashed = false;
  shoutTimer = 1000;
}

void Mob::unleash()
{
  unleashed = true;
}

bool Mob::wasUnleashed()
{
  return unleashed;
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

bool Mob::hasCaught()
{
  int width = 0;
  int height = 0;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  if(pos.x + width - 100 > Monster::inst->getDistance())
  {
    return true;
  }

  return false;
}

void Mob::update()
{
  if(!unleashed) return;
  speed += 5 * util::delta_time;
  pos.x += speed * util::delta_time;

  shoutTimer -= 1000 * util::delta_time;

  if(shoutTimer <= 0)
  {
    shouts.at(util::rand(shouts.size() - 1)).play();
    shoutTimer = util::rand(1000);
  }
}
