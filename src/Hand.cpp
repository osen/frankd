#include "Hand.h"
#include "util.h"
#include "Monster.h"
#include "Camera.h"

#include <iostream>

SDL_Texture* Hand::texture;
util::Sound Hand::grab;

Hand::Hand(int id)
{
  this->clientId = id;

  if(id == 3)
  {
    pos.x = 450;
    pos.y = 400;
  }
  else
  {
    pos.x = 650;
    pos.y = 400;
  }
}

void Hand::update()
{
  int numkeys = 0;
  const Uint8* state = SDLD_GetKeyboardState(clientId, &numkeys);

  glm::vec2 oldPos = pos;

  if(state[38])
  {
    pos.y -= 300 * util::delta_time;
  }
  else if(state[40])
  {
    pos.y += 300 * util::delta_time;
  }

  if(state[39])
  {
    pos.x += 300 * util::delta_time;
  }
  else if(state[37])
  {
    pos.x -= 300 * util::delta_time;
  }

  glm::vec2 mPos;
  mPos.y = 400;
  mPos.x = Monster::inst->getDistance() + 50;

  while(glm::distance(pos, mPos) > 150)
  {
    pos -= glm::normalize(pos - mPos);
  }
}

void Hand::draw()
{
  glm::vec2 offset = Camera::inst->getOffset();
  SDL_Rect r = { 0 };
  r.x = pos.x + offset.x;
  r.y = pos.y + offset.y;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
}
