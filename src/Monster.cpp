#include "Monster.h"
#include "Foot.h"
#include "Hand.h"
#include "util.h"
#include "Camera.h"

std::shared_ptr<Monster> Monster::inst;
SDL_Texture* Monster::texture;
util::Sound Monster::fall;

Monster::Monster()
{
  leftFoot = std::make_shared<Foot>(1);
  rightFoot = std::make_shared<Foot>(2);
  leftHand = std::make_shared<Hand>(3);
  rightHand = std::make_shared<Hand>(4);

  fallAmount = 0;
  falling = true;
}

bool Monster::hasFallen()
{
  if(fallAmount > 10)
  {
    return true;
  }

  return false;
}

float Monster::getDistance()
{
  return (leftFoot->pos.x + rightFoot->pos.x) / 2;
}

void Monster::update()
{
  leftFoot->update();
  rightFoot->update();
  leftHand->update();
  rightHand->update();

  if(!leftFoot->hasPressure() && !rightFoot->hasPressure())
  {
    fallAmount += 100 * util::delta_time;

    if(!falling)
    {
      if(fallAmount > 50)
      {
        fall.play();
        falling = true;
      }
    }
  }
  else
  {
    fallAmount -= 100 * util::delta_time;
  }

  if(fallAmount > 100) fallAmount = 100;
  if(fallAmount < 0)
  {
    fallAmount = 0;
    falling = false;
  }
}

void Monster::draw()
{
  float middleX = (leftFoot->pos.x + rightFoot->pos.x) / 2 - 25;
  glm::vec2 offset = Camera::inst->getOffset();

  SDL_Rect r = { 0 };
  r.x = middleX + offset.x;
  r.y = 300 + (1 * fallAmount) + offset.y;
  SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
  SDL_RenderCopy(util::sdl_renderer, texture, NULL, &r);

  leftFoot->draw();
  rightFoot->draw();
  leftHand->draw();
  rightHand->draw();
}
