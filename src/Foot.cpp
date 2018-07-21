#include "Foot.h"
#include "util.h"
#include "Monster.h"

#include <iostream>

SDL_Texture* Foot::texture;

Foot::Foot(int id)
{
  this->clientId = id;

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

  util::Vec2 oldPos = pos;

  if(state[39])
  {
    pos.x ++;
  }
  else if(state[37])
  {
    pos.x --;
  }

  collision(oldPos);
}

void Foot::collision(util::Vec2& oldPos)
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
}

void Foot::draw()
{
  SDL_Rect r = { 0 };
  r.x = pos.x;
  r.y = pos.y;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);
}
