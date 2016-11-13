#include <ctime>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "main.h"

#include "engine/specator.h"

#include "math/fractal.h"
#include "math/matrix.h"
#include "math/point.h"

#include "plot/colour.h"
#include "plot/renderer.h"

int main(int argc, char *argv[])
{
  srandom(time(0));
  Renderer renderer;
  Specator specator;

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

  Fractal3D f;
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.3, -0.7, 0.3),
                                       Point3D(0, 0, 0), Colour(196, 81, 12)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.611, 0.611, 0.611) * Matrix3D(Matrix3D::ROTATE, 0, 1.12, 0),
                                       Point3D(50, -50, 0), Colour(30, 215, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.591, 0.591, 0.591) * Matrix3D(Matrix3D::ROTATE, 1.03, 1.04, 0),
                                       Point3D(-20, -52, 37), Colour(125, 231, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.540, 0.540, 0.540) * Matrix3D(Matrix3D::ROTATE, -1.23, 1.18, 0),
                                       Point3D(-24, -43, -35), Colour(68, 240, 0)));
  //f.maxiter /= 8;
  /*Fractal3D f;
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5) * Matrix3D(Matrix3D::ROTATE, 0, 0, 0),
                                         Point3D(0, 0, 0), Colour(0, 0, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5),
                                         Point3D(100, 0, 0), Colour(255, 0, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5),
                                         Point3D(0, 100, 0), Colour(0, 255, 0)));
  f.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.5, 0.5, 0.5),
                                         Point3D(0, 0, 100), Colour(0, 0, 255)));*/
  f.pos.z = 200;

  double px = 0, py = 0;
  int last_ticks = SDL_GetTicks();
  bool quit = false;
  while (!quit)
  {
    //specator.set_pos(Point3D(px - 320, py - 240, 0));
    specator.set_yaw((px - 320)/320);
    specator.set_pitch((py - 240)/240);
    //specator.turn_right((px - 320)/32000);
    //specator.turn_down((py - 240)/24000);
    specator.update();
    background.draw();
    /*f.pos.x = px - 320;
    f.pos.y = py - 240;*/
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
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              quit = true;
              break;
            case SDLK_UP:
              specator.move_forwards(10);
              break;
            case SDLK_DOWN:
              specator.move_forwards(-10);
              break;
            case SDLK_LEFT:
              specator.move_sidewards(-10);
              break;
            case SDLK_RIGHT:
              specator.move_sidewards(10);
              break;
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

