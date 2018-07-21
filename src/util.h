#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>

#include <string>
#include <memory>

namespace util
{

struct Spritesheet
{
  int rows;
  int columns;
  SDL_Texture* texture;
  int w;
  int h;
};

extern SDL_Window* sdl_window;
extern SDL_Surface* sdl_screen;
extern SDL_Renderer* sdl_renderer;
extern bool should_exit;
extern double delta_time;

void sdl_initialize(std::string title, int width, int height);
void update_deltatime();
void sdl_clearscreen(int r, int g, int b);
void sdl_blit(SDL_Surface* src, SDL_Surface* dest, int x, int y);
//bool sdl_keydown(SDL_Keycode key);

SDL_Texture* sdl_loadtexture(std::string path);

Spritesheet* SpritesheetLoad(std::string path, int columns, int rows);
void SpritesheetFree(Spritesheet* ctx);
void SpritesheetBlit(Spritesheet* ctx, int column, int row, int x, int y);

void error(std::string message);

struct FontImpl;

class Font
{
  std::shared_ptr<FontImpl> impl;

public:
  void load(std::string path);
  int getWidth(std::string sample);
  int getHeight();
  void draw(std::string message, int x, int y);

};

}

#endif
