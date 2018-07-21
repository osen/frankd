#include "Monster.h"
#include "Foot.h"
#include "util.h"

std::shared_ptr<Monster> Monster::inst;
SDL_Texture* Monster::texture;

Monster::Monster()
{
  leftFoot = std::make_shared<Foot>(1);
  rightFoot = std::make_shared<Foot>(2);
}

void Monster::update()
{
  leftFoot->update();
  rightFoot->update();
}

void Monster::draw()
{
  float middleX = (leftFoot->pos.x + rightFoot->pos.x) / 2;

  SDL_Rect r = { 0 };
  r.x = middleX;
  r.y = 300;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);

  leftFoot->draw();
  rightFoot->draw();
}
