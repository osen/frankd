#include "Player.h"

#include <iostream>

util::Spritesheet* Player::ss;
std::vector<Player> Player::all;

Player::Player(int id)
{
  this->id = id;
  x = 100;
  y = 200;
  frame = 0;
  direction = 3;
  moving = 0;

  if(id == 2)
  {
    x = 300;
    direction = 1;
  }
  else if(id == 3)
  {
    x = 200;
    y = 100;
    direction = 0;
  }
  else if(id == 4)
  {
    x = 200;
    y = 300;
    direction = 2;
  }
}

void Player::update()
{
  int numkeys = 0;
  const Uint8* state = SDLD_GetKeyboardState(id, &numkeys);
  moving = 0;

  if(state[39] == 1)
  {
    direction = 3;
    x += 200 * util::delta_time;
    moving = 1;
  }
  else if(state[37] == 1)
  {
    direction = 1;
    x -= 200 * util::delta_time;
    moving = 1;
  }

  if(moving)
  {
    frame += 20 * util::delta_time;
  }
  else
  {
    frame = 0;
  }
}

void Player::draw()
{
  //std::cout << x << std::endl;
  util::SpritesheetBlit(ss, frame,  moving * 4 + direction, x, y);
}
