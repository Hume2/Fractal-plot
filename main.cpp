#include <stdio.h>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "main.h"

#include "math/fractal.h"
#include "math/matrix.h"
#include "math/point.h"

#include "plot/colour.h"
#include "plot/renderer.h"

int main(int argc, char *argv[])
{
  Renderer renderer;

  Fractal f;
  f.branches.push_back(Matrix2D(0.5, 0.0, 0.0,
                                0.0, 0.5, 0.0,
                                0.0, 0.0, 1.0));
  f.branches.push_back(Matrix2D(0.5, 0.0, 100,
                                0.0, 0.5, 0.0,
                                0.0, 0.0, 1.0));
  f.branches.push_back(Matrix2D(0.5, 0.0,  50,
                                0.0, 0.5, 100,
                                0.0, 0.0, 1.0));

  double p = 0;
  int last_ticks = SDL_GetTicks();
  bool quit = false;
  while (!quit)
  {
    f.draw(Point2D(p, p/2));
    renderer.update_window();
    p += 1;

    int next_ticks = SDL_GetTicks();
    std::cout << (1000 / (next_ticks - last_ticks)) << "FPS" << std::endl;
    last_ticks = next_ticks;

    SDL_Event event;
    bool leftMouseButtonDown;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
         leftMouseButtonDown = false;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
            leftMouseButtonDown = true;
    case SDL_MOUSEMOTION:
        if (leftMouseButtonDown)
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            Renderer::current()->put_pixel(mouseX, mouseY, Colour(0xFF, 0x00, 0x00));
        }
        break;
    case SDL_QUIT:
        quit = true;
        break;
    }
  }

  return 0;
}

