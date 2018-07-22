#include "util.h"

#ifdef _WIN32
  #include <windows.h>
#endif

#include <SDL2/SDL_image.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <vector>

namespace util
{
  SDL_Window* sdl_window;
  SDL_Renderer* sdl_renderer;
  bool should_exit;
  double delta_time;

  ALCdevice* device;
  ALCcontext* context;
  std::vector<ALuint> audioSources;

  int rand(int max)
  {
    return ::rand() % (max + 1);
  }

  void log(std::string message)
  {
    std::cout << "[util]" << message << std::endl;
  }

  void cleanup()
  {
    log("Cleaning up OpenAL");

    for(size_t asi = 0; asi < audioSources.size(); asi++)
    {
      ALuint& as = audioSources.at(asi);

      while(true)
      {
        ALint state = 0;

        alGetSourcei(as, AL_SOURCE_STATE, &state);

        if(state == AL_STOPPED)
        {
          alDeleteSources(1, &as);
          break;
        }

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
      }
    }

    audioSources.clear();

    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    log("Cleaning up SDL2");
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
  }

  bool colliding(SDL_Rect& a, SDL_Rect& b)
  {
    bool cX = false;
    bool cY = false;

    if(a.x < b.x)
    {
      if(a.x + a.w >= b.x)
      {
        cX = true;
      }
    }
    else
    {
      if(b.x + b.w >= a.x)
      {
        cX = true;
      }
    }

    if(!cX) return false;

    if(a.y < b.y)
    {
      if(a.y + a.h >= b.y)
      {
        cY = true;
      }
    }
    else
    {
      if(b.y + b.h >= a.y)
      {
        cY = true;
      }
    }

    if(!cY) return false;

    return true;
  }

  void error(std::string message)
  {
    std::cout << "Error: " << message << std::endl;
#ifdef _WIN32
    MessageBox(0, message.c_str(), "SDL Program Error", 0);
#endif
    exit(1);
  }

  void sdl_initialize(std::string title, int width, int height)
  {
    log("Initializing SDL2");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      error("Failed to initialize SDL");
    }

    sdl_window = SDL_CreateWindow(title.c_str(),
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

    if (!sdl_window)
    {
      error("Failed to open window");
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

    log("Initializing OpenAL");
    // Open up the OpenAL device
    device = alcOpenDevice(NULL);

    if(device == NULL)
    {
      std::cout << "Failed to open device" << std::endl;
      return;
      throw std::exception();
    }

    // Create audio context
    context = alcCreateContext(device, NULL);

    if(context == NULL)
    {
      alcCloseDevice(device);
      std::cout << "Failed to create context" << std::endl;
      throw std::exception();
    }

    // Set as current context
    if(!alcMakeContextCurrent(context))
    {
      alcDestroyContext(context);
      alcCloseDevice(device);
      std::cout << "Failed to make context current" << std::endl;
      throw std::exception();
    }

    atexit(cleanup);
  }

  void update_deltatime()
  {
    static Uint32 now = 0;
    static Uint32 last = 0;

    now = SDL_GetTicks();
    delta_time = (now - last) / 1000.0f;
    last = now;

    for(size_t asi = 0; asi < audioSources.size(); asi++)
    {
      ALuint& as = audioSources.at(asi);
      ALint state = 0;

      alGetSourcei(as, AL_SOURCE_STATE, &state);

      if(state == AL_STOPPED)
      {
        //std::cout << "Deleting audio source" << std::endl;
        alDeleteSources(1, &as);
        audioSources.erase(audioSources.begin() + asi);
        asi--;
      }
    }
  }

  void sdl_clearscreen(int r, int g, int b)
  {
    SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 255);
    SDL_RenderClear(sdl_renderer);
  }

  void sdl_blit(SDL_Texture* src, int x, int y)
  {
    SDL_Rect r = { 0 };
    r.x = x;
    r.y = y;
    SDL_QueryTexture(src, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(sdl_renderer, src, NULL, &r);
  }

/*
  bool sdl_keydown(SDL_Keycode key)
  {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[(Uint8)key]) return true;
    return false;
  }
*/

  Spritesheet* SpritesheetLoad(std::string path, int columns, int rows)
  {
    Spritesheet* rtn = new Spritesheet();
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(!surface) return NULL;

    rtn->w = surface->w;
    rtn->h = surface->h;
    rtn->rows = rows;
    rtn->columns = columns;

    rtn->texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    SDL_FreeSurface(surface);

    return rtn;
  }

  void SpritesheetFree(Spritesheet* ctx)
  {
    SDL_DestroyTexture(ctx->texture);
    delete ctx;
  }

  void SpritesheetBlit(Spritesheet* ctx, int column, int row, int x, int y)
  {
    SDL_Rect sr = {0};

    column = column % ctx->columns;
    row = row % ctx->rows;

    sr.w = ctx->w / ctx->columns;
    sr.h = ctx->h / ctx->rows;
    sr.x = sr.w * column;
    sr.y = sr.h * row;

    SDL_Rect dr = {0};

    dr.x = x;
    dr.y = y;
    dr.w = sr.w;
    dr.h = sr.h;

    SDL_RenderCopy(sdl_renderer, ctx->texture, &sr, &dr);
  }

  SDL_Texture* sdl_loadtexture(std::string path)
  {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(!surface) throw std::exception();
    SDL_Texture* rtn = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    if(!rtn) throw std::exception();
    SDL_FreeSurface(surface);

    return rtn;
  }
}
