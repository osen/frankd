#include "Background.h"
#include "Camera.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>

std::shared_ptr<Background> Background::inst;
std::vector<SDL_Texture*> Background::grounds;
std::vector<SDL_Texture*> Background::backgrounds;
std::vector<SDL_Texture*> Background::skys;

void Background::draw()
{
  int tw = 0;
  int th = 0;
  SDL_QueryTexture(grounds.at(0), NULL, NULL, &tw, &th);
  float curr = -tw * 2;
  int gt = 0;
  int st = 0;
  int bt = 0;

  while(true)
  {
    curr += tw;
    bt++;
    if(bt >= backgrounds.size()) bt = 0;
    glm::vec2 offset = Camera::inst->getOffset();
    SDL_Rect r = { 0 };
    r.w = tw;

    if(curr > Camera::inst->pos.x / 2 - tw)
    {
      r.x = curr + offset.x / 2;
      //r.y = -200 + th + offset.y;
      r.y = 100;
      r.h = glutGet(GLUT_WINDOW_HEIGHT);
      //r.h = th;
      SDL_RenderCopy(util::sdl_renderer, backgrounds.at(bt), NULL, &r);
    }

    if(curr > Camera::inst->pos.x + tw * 2) break;
  }

  curr = -tw * 2;

  while(true)
  {
    curr += tw;
    gt++;
    if(gt >= grounds.size()) gt = 0;
    glm::vec2 offset = Camera::inst->getOffset();
    SDL_Rect r = { 0 };
    r.w = tw;

    if(curr > Camera::inst->pos.x - tw)
    {
      r.x = curr + offset.x;
      r.y = 450 + offset.y;
      r.h = th;
      SDL_RenderCopy(util::sdl_renderer, grounds.at(gt), NULL, &r);
    }

    if(curr > Camera::inst->pos.x + tw * 2) break;
  }

  curr = -tw * 2;

  while(true)
  {
    curr += tw;
    st++;
    if(st >= skys.size()) st = 0;
    glm::vec2 offset = Camera::inst->getOffset();
    SDL_Rect r = { 0 };
    r.w = tw;

    if(curr > Camera::inst->pos.x / 4 - tw)
    {
      r.x = curr + offset.x / 4;
      r.y = -150 + offset.y;
      r.h = th;
      SDL_RenderCopy(util::sdl_renderer, skys.at(st), NULL, &r);
    }

    if(curr > Camera::inst->pos.x + tw * 2) break;
  }
}
