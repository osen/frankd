#include "Camera.h"
#include "Mob.h"
#include "util.h"
#include "Monster.h"
#include "Foot.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

util::Font f;

void update()
{
  Mob::inst->update();
  Monster::inst->update();
}

void draw(int id)
{
  if(id == 1)
  {
    util::sdl_clearscreen(0, 0, 100);
  }
  else
  {
    util::sdl_clearscreen(0, 100, 0);
  }


  Camera::inst->draw();
  Mob::inst->draw();
  Monster::inst->draw();

  std::stringstream ss;
  ss << "Distance travelled: " << Monster::inst->getDistance();
  f.draw(ss.str(), 10, 0);
}

void load_resources()
{
  Mob::texture = util::sdl_loadtexture("resources/mob.png");
  Foot::texture = util::sdl_loadtexture("resources/foot.png");
  Monster::texture = util::sdl_loadtexture("resources/body.png");

  f.load("resources/font.png");
}

void cleanup()
{

}

int main()
{
  util::sdl_initialize("Frankendine", 800, 600);
  atexit(cleanup);

  load_resources();

  Camera::inst = std::make_shared<Camera>();
  Monster::inst = std::make_shared<Monster>();
  Mob::inst = std::make_shared<Mob>();

  SDL_Event e = {0};
  bool quit = false;

  while(!quit)
  {
    util::update_deltatime();

    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(e.type == SDL_VIDEOEXPOSE)
      {
        draw(e.client_id);
        SDL_RenderPresent(util::sdl_renderer);
      }
      else if(e.type == SDL_KEYDOWN)
      {
        //std::cout << "Key Down: " << e.key.keysym.sym << std::endl;
      }
      else if(e.type == SDL_KEYUP)
      {
        //std::cout << "Key Up:" << e.key.keysym.sym << std::endl;
      }
    }

    update();
    SDL_Delay(10);
    //SDL_Delay(1);
  }

  return 0;
}

