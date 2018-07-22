#include "Camera.h"
#include "Mob.h"
#include "util.h"
#include "Monster.h"
#include "Foot.h"
#include "Background.h"
#include "Hand.h"
#include "Overlay.h"

#include <GL/glut.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

util::Font f;
util::Sound s;
util::Sound lightning;

void update()
{
  if(!Mob::inst->hasCaught())
  {
    Mob::inst->update();
    Monster::inst->update();
  }
}

void draw(int id)
{
  if(id == 1)
  {
    //util::sdl_clearscreen(0, 0, 100);
  }
  else
  {
    //util::sdl_clearscreen(0, 100, 0);
  }

  util::sdl_clearscreen(22, 49, 68);

  Camera::inst->draw();
  Background::inst->draw();

  Mob::inst->draw();
  Monster::inst->draw();
  Overlay::inst->draw();

  std::stringstream ss;
  ss << "Distance travelled: " << Monster::inst->getDistance();
  f.draw(ss.str(), 10, 0);

  int sw = glutGet(GLUT_WINDOW_WIDTH);
  int sh = glutGet(GLUT_WINDOW_HEIGHT);

  if(!Mob::inst->wasUnleashed())
  {
    std::string msg = "Press a key to unleash the mob!";
    f.draw(msg, sw / 2 - f.getWidth(msg) / 2, sh / 2 - f.getHeight() / 2);
  }

  if(Mob::inst->hasCaught())
  {
    std::string msg = "Monster was caught by the mob! Press 'R' to restart!";
    f.draw(msg, sw / 2 - f.getWidth(msg) / 2, sh / 2 - f.getHeight() / 2);
  }
}

void load_resources()
{
  Mob::texture = util::sdl_loadtexture("resources/mob.png");
  Foot::texture = util::sdl_loadtexture("resources/foot.png");
  Foot::texturel = util::sdl_loadtexture("resources/footl.png");
  Hand::texture = util::sdl_loadtexture("resources/hand.png");
  Hand::texturel = util::sdl_loadtexture("resources/handl.png");
  Monster::texture = util::sdl_loadtexture("resources/body.png");
  Background::grounds.push_back(util::sdl_loadtexture("resources/ground1.png"));
  Background::grounds.push_back(util::sdl_loadtexture("resources/ground2.png"));
  Background::skys.push_back(util::sdl_loadtexture("resources/sky1.png"));
  Background::backgrounds.push_back(util::sdl_loadtexture("resources/background1.png"));
  Background::backgrounds.push_back(util::sdl_loadtexture("resources/background2.png"));
  Overlay::texture = util::sdl_loadtexture("resources/overlay.png");

  f.load("resources/font.png");
  s.load("resources/welcome.ogg");
  lightning.load("resources/lightning.ogg");

  for(int i = 1; i <= 15; i++)
  {
    std::stringstream ss;
    ss << "resources/fgrunt_" << i << ".ogg";
    Monster::grunts.push_back(util::Sound(ss.str()));
  }

  for(int i = 1; i <= 15; i++)
  {
    std::stringstream ss;
    ss << "resources/fgrunt_" << i << ".ogg";
    Mob::shouts.push_back(util::Sound(ss.str()));
  }

  Foot::plod.load("resources/footstep.ogg");
}

void cleanup()
{

}

void restart()
{
  Camera::inst = std::make_shared<Camera>();
  Monster::inst = std::make_shared<Monster>();
  Mob::inst = std::make_shared<Mob>();
  Overlay::inst = std::make_shared<Overlay>();
}

int main()
{
  util::sdl_initialize("Frankendine", 800, 600);
  atexit(cleanup);

  load_resources();

  restart();

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
        //s.play();

        if(!Mob::inst->wasUnleashed())
        {
          lightning.play();
          Mob::inst->unleash();
        }

        if(e.key.keysym.sym == 82) restart();
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

