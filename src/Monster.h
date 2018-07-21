#include "util.h"

#include <memory>

struct Foot;

struct Monster
{
  static std::shared_ptr<Monster> inst;
  static SDL_Texture* texture;

  std::shared_ptr<Foot> leftFoot;
  std::shared_ptr<Foot> rightFoot;
  //std::shared_ptr<Hand> leftHand;
  //std::shared_ptr<Hand> rightHand;
  float fallAmount;
  bool hasFallen();

  Monster();
  void draw();
  void update();

};
