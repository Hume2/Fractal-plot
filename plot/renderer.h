#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Colour;

class Renderer
{
  public:
    Renderer();
    ~Renderer();

    static Renderer* current();

    void update_window();

    void put_pixel(int x, int y, Colour c);

    SDL_Window* get_window() const {
      return window;
    }

  private:
    static Renderer* s_current;

    SDL_Window* window;
    SDL_Surface* screen_surface;
    Uint32* pixels;
};

#endif // RENDERER_H
