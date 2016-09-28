#include <ctime>
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
  srandom(time(0));
  Renderer renderer;

  Fractal background;
  background.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(0, 0)));
  background.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(640, 0)));
  background.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(0, 480)));
  background.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(640, 480)));
  background.calculate_chance_suma();
  background.colour = Colour(100, 200, 255);

  Fractal f;
  f.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(0, 0)));
  f.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(100, 0)));
  f.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(0, 100)));
  f.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.5f, 0.5f),
                                       Point2D(100, 100)));
  f.calculate_chance_suma();
  f.colour = Colour(64, 128, 0);
  f.maxiter /= 10;

  Fractal g = f;
  g.colour = Colour(255, 0, 0);

  double px = 0, py = 0;
  int last_ticks = SDL_GetTicks();
  bool quit = false;
  while (!quit)
  {
    background.draw(Point2D(0, 0));
    g.draw(Point2D(100, 100));
    f.draw(Point2D(px, py));
    renderer.update_window();

    int next_ticks = SDL_GetTicks();
    std::cout << (1000 / (next_ticks - last_ticks + 1)) << "FPS" << std::endl;
    last_ticks = next_ticks;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type)
      {
        case SDL_MOUSEMOTION:
          px = event.motion.x;
          py = event.motion.y;
        break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) {
            quit = true;
          }
          break;
        case SDL_QUIT:
          quit = true;
          break;
      }
    }
  }

  return 0;
}

