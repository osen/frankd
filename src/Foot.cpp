#include "Foot.h"
#include "util.h"
#include "Monster.h"

#include <iostream>

SDL_Texture* Foot::texture;

Foot::Foot(int id)
{
  this->clientId = id;
  pressure = false;

  if(id == 1)
  {
    pos.x = 500;
    pos.y = 500;
  }
  else
  {
    pos.x = 600;
    pos.y = 500;
  }
}

void Foot::update()
{
  int numkeys = 0;
  const Uint8* state = SDLD_GetKeyboardState(clientId, &numkeys);

  glm::vec2 oldPos = pos;
  pressure = false;

  if(state[38])
  {
    if(!Monster::inst->hasFallen()) pos.y -= 300 * util::delta_time;
  }
  else if(state[40])
  {
    if(!Monster::inst->hasFallen()) pos.y += 300 * util::delta_time;
    pressure = true;
  }

  if(!hasPressure())
  {
    if(state[39])
    {
      if(!Monster::inst->hasFallen()) pos.x += 300 * util::delta_time;
    }
    else if(state[37])
    {
      if(!Monster::inst->hasFallen()) pos.x -= 300 * util::delta_time;
    }
  }

  if(Monster::inst->hasFallen()) pos.y += 300 * util::delta_time;

  collision(oldPos);
}

void Foot::collision(glm::vec2& oldPos)
{
  std::shared_ptr<Foot> c;

  if(Monster::inst->leftFoot.get() == this)
  {
    c = Monster::inst->rightFoot;
  }
  else
  {
    c = Monster::inst->leftFoot;
  }

  SDL_Rect a;
  a.x = pos.x;
  a.y = pos.y;
  SDL_QueryTexture(texture, NULL, NULL, &a.w, &a.h);

  SDL_Rect b = a;
  b.x = c->pos.x;
  b.y = c->pos.y;

  if(util::colliding(a, b))
  {
    pos = oldPos;
  }

  if(oldPos.x != pos.x)
  {
    while(glm::distance(pos, c->pos) > 150)
    {
      pos -= glm::normalize(pos - c->pos);
    }
  }

/*
  if(glm::distance(pos, c->pos) > 150)
  {
    pos.x = oldPos.x;
  }
*/

  if(pos.y < 400) pos.y = 400;
  if(pos.y > 500) pos.y = 500;
}

/*
float Foot::getOffsetY()
{
  return 500 - pos.y;
}
*/

bool Foot::hasPressure()
{
  if(pos.y < 490) return false;
  return pressure;
}

void Foot::draw()
{
  SDL_Rect r = { 0 };
  r.x = pos.x;
  r.y = pos.y;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
}
