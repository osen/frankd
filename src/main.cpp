#include "Player.h"
#include "Apple.h"
#include "util.h"

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
  for(auto it = Player::all.begin(); it != Player::all.end(); it++)
  {
    it->update();
  }
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

  for(auto it = Player::all.begin(); it != Player::all.end(); it++)
  {
    it->draw();
  }

  for(auto it = Apple::all.begin(); it != Apple::all.end(); it++)
  {
    it->draw();
  }

  std::stringstream ss;
  ss << "Player: " << id;
  f.draw(ss.str(), 500, 50);
}

void load_resources()
{
  Player::ss = util::SpritesheetLoad("resources/link.png", 10, 8);
  Apple::texture = util::sdl_loadtexture("resources/heart.png");

  f.load("resources/font.png");
}

void cleanup()
{
  Player::all.clear();
  Apple::all.clear();
}

int main()
{
  util::sdl_initialize("Zelda III Arena", 800, 600);
  atexit(cleanup);

  load_resources();

  Player::all.push_back(Player(1));
  Player::all.push_back(Player(2));
  Player::all.push_back(Player(3));
  Player::all.push_back(Player(4));

  Apple::all.push_back(Apple());

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

