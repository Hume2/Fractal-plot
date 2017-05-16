#include <ctime>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "main.h"

#include "engine/model_manager.h"
#include "engine/specator.h"

#include "math/fractal.h"
#include "math/matrix.h"

#include "plot/renderer.h"

int main(int argc, char *argv[])
{
  srandom(time(0));
  Renderer renderer;
  Specator specator;

  /*Fractal3D background;
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.009f, 0.7f, 0.7f) * Matrix3D(Matrix3D::ROTATE, 0.5, 0.7, 1),
                                       Point3D(100, 0, 0), Colour(255, 128, 128)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.009f, 0.7f, 0.7f) * Matrix3D(Matrix3D::ROTATE, 0.5, 0.7, 1),
                                       Point3D(-100, 0, 0), Colour(128, 255, 255)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.7f, 0.009f, 0.7f) * Matrix3D(Matrix3D::ROTATE, 1, 0.5, 0.7),
                                       Point3D(0, 100, 0), Colour(128, 255, 128)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.7f, 0.009f, 0.7f) * Matrix3D(Matrix3D::ROTATE, 1, 0.5, 0.7),
                                       Point3D(0, -100, 0), Colour(255, 128, 255)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.7f, 0.7f, 0.009f) * Matrix3D(Matrix3D::ROTATE, 0.7, 1, 0.5),
                                       Point3D(0, 0, 100), Colour(128, 128, 255)));
  background.branches.push_back(Fractal3D::Branch(Matrix3D(Matrix3D::SCALE, 0.7f, 0.7f, 0.009f) * Matrix3D(Matrix3D::ROTATE, 0.7, 1, 0.5),
                                       Point3D(0, 0, -100), Colour(255, 255, 128)));
  background.pos = Point3D(0, 0, 0);
  background.maxiter *= 1;
  background.offscreen_factor = 100;*/

  ModelManager mm;
  mm.init_from_lisp();
  //mm.load();
  mm.save();

  Fractal3D f = mm.fabricate("test:tetrahedron");
  f.pos.z = 0;
  f.maxiter *= 1000;

  Fractal3D background = mm.fabricate("test:sky");
  background.pos = Point3D(0, 0, 0);
  background.maxiter *= 1;
  background.offscreen_factor = 100;
  //return 0;

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
    background.pos = specator.get_pos();
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

