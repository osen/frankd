#include "util.h"

#include <memory>

struct Foot;
struct Hand;

struct Monster
{
  static std::shared_ptr<Monster> inst;
  static SDL_Texture* texture;
  static util::Sound fall;

  std::shared_ptr<Foot> leftFoot;
  std::shared_ptr<Foot> rightFoot;
  std::shared_ptr<Hand> leftHand;
  std::shared_ptr<Hand> rightHand;
  float fallAmount;
  bool hasFallen();
  float getDistance();

  bool falling;

  Monster();
  void draw();
  void update();

};
