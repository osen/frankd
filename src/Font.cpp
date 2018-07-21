#include "util.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include <cstring>

namespace util
{

struct Pixel
{
  int r;
  int g;
  int b;
  int a;
};

struct Glyph
{
  char c;
  int x;
  int y;
  int width;
  int height;
  SDL_Texture* texture;
};

static const char *characters = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

struct FontImpl
{
  SDL_Texture* texture;
  SDL_Surface* surface;
  std::vector<Glyph> glyphs;

  FontImpl() : texture(NULL), surface(NULL) { }

  ~FontImpl()
  {
    if(texture) SDL_DestroyTexture(texture);
    if(surface) SDL_FreeSurface(surface);
  }

  Pixel getPixel(int x, int y)
  {
    Pixel p;

    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format.BitsPerPixel;
    p.r = *target_pixel;
    p.g = *(target_pixel + 1);
    p.b = *(target_pixel + 2);

    p.a = 255;

    if(surface->format.BitsPerPixel == 4)
    {
      p.a = *(target_pixel + 3);
    }

    return p;
  }

  void generateGlyphs()
  {
    int x = 0;
    int texHeight = 0;
    int texWidth = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

    for(size_t i = 0; i < strlen(characters); i++)
    {
      Glyph g = {0};
      g.c = characters[i];
      g.texture = texture;
      g.y = 0;
      g.height = texHeight;

      while(1)
      {
        if(x >= texWidth)
        {
          util::error("Texture did not contain correct number of characters");
        }

        if(dirtyColumn(x) == true)
        {
          g.x = x;
          break;
        }

        x++;
      }

      while(1)
      {
        if(x >= texWidth)
        {
          util::error("Texture too small to fit current character");
        }

        if(dirtyColumn(x) == 0)
        {
          g.width = x - g.x;
          break;
        }

        x++;
      }

      glyphs.push_back(g);

      if(g.c == '-')
      {
        g.c = ' ';
        g.height = texHeight;
        glyphs.push_back(g);
      }
    }
  }

  bool dirtyColumn(int x)
  {
    int texHeight = 0;
    int texWidth = 0;

    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

    for(int y = 0; y < texHeight; y++)
    {
      Pixel col = getPixel(x, y);

      if(col.a != 0) return true;
    }

    return false;
  }

  Glyph getGlyph(char c)
  {
    size_t i = 0;
    Glyph rtn = {0};

    for(i = 0; i < glyphs.size(); i++)
    {
      if(glyphs.at(i).c == c)
      {
        return glyphs.at(i);
      }
    }

    throw std::exception();
  }
};

void Font::load(std::string path)
{
  impl = std::make_shared<FontImpl>();

  impl->surface = IMG_Load(path.c_str());
  if(!impl->surface) throw std::exception();

  impl->texture = SDL_CreateTextureFromSurface(util::sdl_renderer, impl->surface);
  //SDL_FreeSurface(surface);

  impl->generateGlyphs();
}

int Font::getHeight()
{
  Glyph g = impl->getGlyph('A');

  return g.height;
}

int Font::getWidth(std::string sample)
{
  int rtn = 0;
  int space = 0;

  for(size_t i = 0; i < sample.length(); i++)
  {
    Glyph g = impl->getGlyph(sample.at(i));

    rtn += space + g.width;
    space = 1;
  }

  return rtn;
}

void Font::draw(std::string text, int x, int y)
{
  for(size_t i = 0; i < text.length(); i++)
  {
    Glyph g = impl->getGlyph(text.at(i));

    SDL_Rect sr = {0};

    sr.w = g.width;
    sr.h = g.height;
    sr.x = g.x;
    sr.y = g.y;

    SDL_Rect dr = {0};

    dr.x = x;
    dr.y = y;
    dr.w = sr.w;
    dr.h = sr.h;

    if(g.c != ' ')
    {
      SDL_RenderCopy(util::sdl_renderer, impl->texture, &sr, &dr);
    }

    x += dr.w;
  }
}

}
