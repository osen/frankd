#ifndef SDL2_SDL_H
#define SDL2_SDL_H

#include <stdint.h>

#define SDL_INIT_VIDEO 24
#define SDL_WINDOWPOS_UNDEFINED -1
#define SDL_RENDERER_ACCELERATED 2

#define SDL_QUIT 1
#define SDL_VIDEOEXPOSE 2
#define SDL_KEYDOWN 3
#define SDL_KEYUP 4

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

typedef uint8_t Uint8;
typedef uint32_t Uint32;
typedef uint32_t SDL_Key;

struct SDL_Rect
{
  int x;
  int y;
  int w;
  int h;
};

struct SDL_Keysym
{
  SDL_Key sym;
};

struct SDL_KeyboardEvent
{
  struct SDL_Keysym keysym;
};

struct SDL_Event
{
  int type;
  int client_id;
  struct SDL_KeyboardEvent key;
};

struct SDL_PixelFormat
{
  Uint8 BitsPerPixel;
};

struct SDL_Surface
{
  struct SDL_PixelFormat format;
  int w;
  int h;
  int pitch;
  unsigned char *pixels;
};

#ifdef __cplusplus
extern "C" {
#endif

int SDL_Init(Uint32 flags);
void SDL_Quit();

int SDL_PollEvent(struct SDL_Event* event);

struct SDL_Window* SDL_CreateWindow(const char* title,
  int x, int y, int w, int h, Uint32 flags);

void SDL_DestroyWindow(struct SDL_Window* window);

struct SDL_Renderer* SDL_CreateRenderer(struct SDL_Window* window,
  int index, Uint32 flags);

void SDL_DestroyRenderer(struct SDL_Renderer* renderer);

int SDL_SetRenderDrawColor(struct SDL_Renderer* renderer,
  Uint8 r, Uint8 g, Uint8 b, Uint8 a);

int SDL_RenderClear(struct SDL_Renderer* renderer);

void SDL_RenderPresent(struct SDL_Renderer* renderer);

void SDL_FreeSurface(struct SDL_Surface* surface);

struct SDL_Texture* SDL_CreateTextureFromSurface(struct SDL_Renderer* renderer,
  struct SDL_Surface* surface);

int SDL_QueryTexture(struct SDL_Texture* texture,
  Uint32* format, int* access, int* w, int* h);

int SDL_RenderCopy(struct SDL_Renderer* renderer, struct SDL_Texture* texture,
  const struct SDL_Rect* srcrect, const struct SDL_Rect* dstrect);

void SDL_DestroyTexture(struct SDL_Texture* texture);

Uint32 SDL_GetTicks();
void SDL_Delay(Uint32 ms);

const Uint8* SDLD_GetKeyboardState(int idx, int* numkeys);

#ifdef __cplusplus
}
#endif

#endif
