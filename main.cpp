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

  Fractal3D background;
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5f, 0.5f, 0.5f),
                                       Point3D(0, 0, 0), Colour(100, 200, 255)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5f, 0.5f, 0.5f),
                                       Point3D(6400, 0, 0), Colour(255, 255, 255)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5f, 0.5f, 0.5f),
                                       Point3D(0, 4800, 0), Colour(255, 255, 255)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5f, 0.5f, 0.5f),
                                       Point3D(6400, 4800, 0), Colour(100, 200, 255)));
  background.pos = Point3D(-3200, -2400, 4000);
  background.maxiter *= 500;

  /*Fractal f;
  f.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.7, -0.5) * Matrix2D(Matrix2D::ROTATE, 0, 0),
                                       Point2D(103, 245), Colour(196, 81, 12)));
  f.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.611, 0.611) * Matrix2D(Matrix2D::ROTATE, 0.45, 0),
                                       Point2D(13, 50), Colour(30, 215, 0)));
  f.branches.push_back(Fractal::Branch(Matrix2D(Matrix2D::SCALE, 0.591, 0.591) * Matrix2D(Matrix2D::ROTATE, -1.03, 0),
                                       Point2D(187, 25), Colour(125, 231, 0)));
  f.calculate_chance_suma();*/
  Fractal3D f;
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5),
                                         Point3D(0, 0, 0), Colour(0, 0, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5),
                                         Point3D(100, 0, 0), Colour(255, 0, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5),
                                         Point3D(0, 100, 0), Colour(0, 255, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5),
                                         Point3D(0, 0, 100), Colour(0, 0, 255)));
  f.pos.z = 400;

  double px = 0, py = 0;
  int last_ticks = SDL_GetTicks();
  bool quit = false;
  while (!quit)
  {
    background.draw();
    f.pos.x = px - 320;
    f.pos.y = py - 240;
    f.draw();
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

