#include "Foot.h"
#include "util.h"
#include "Monster.h"
#include "Camera.h"

#include <iostream>

SDL_Texture* Foot::texture;
SDL_Texture* Foot::texturel;
util::Sound Foot::plod;

Foot::Foot(int id)
{
  this->clientId = id;
  pressure = false;
  begunPressure = true;

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
    if(!Monster::inst->hasFallen()) pos.y -= 400 * util::delta_time;
  }
  else if(state[40])
  {
    if(!Monster::inst->hasFallen()) pos.y += 400 * util::delta_time;
    pressure = true;
  }

  if(!hasPressure())
  {
    if(state[39])
    {
      if(!Monster::inst->hasFallen()) pos.x += 400 * util::delta_time;
    }
    else if(state[37])
    {
      if(!Monster::inst->hasFallen()) pos.x -= 400 * util::delta_time;
    }
  }

  if(Monster::inst->hasFallen()) pos.y += 300 * util::delta_time;

  collision(oldPos);

  if(pos.y < 490)
  {
    begunPressure = false;
  }

  if(!begunPressure)
  {
    if(hasPressure())
    {
      begunPressure = true;
      plod.play();
    }
  }

  //pos.x += 1;
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

  float am = 1;

  while(util::colliding(a, b))
  {
    a.x += am;
    if(!util::colliding(a, b)) break;
    a.x -= am;
    a.x -= am;
    if(!util::colliding(a, b)) break;
    a.x += am;
    a.y += am;
    if(!util::colliding(a, b)) break;
    a.y -= am;
    a.y -= am;
    if(!util::colliding(a, b)) break;
    a.y += am;

    am++;
  }

  pos.x = a.x;
  pos.y = a.y;

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
  glm::vec2 offset = Camera::inst->getOffset();
  SDL_Rect r = { 0 };
  r.x = pos.x + offset.x;
  r.y = pos.y + offset.y;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);

  if(clientId == 1)
  {
    SDL_RenderCopy(util::sdl_renderer, texturel, NULL, &r);
  }
  else
  {
    SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
  }
}
