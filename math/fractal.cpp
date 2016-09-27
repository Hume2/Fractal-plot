#include <stdio.h>
#include <iostream>
#include <random>

#include "fractal.h"

#include "rectangle.h"
#include "../plot/colour.h"
#include "../plot/renderer.h"

Fractal::Fractal() :
  branches(),
  maxiter(1000),
  chance_suma(),
  colour(0, 0, 0)
{

}

void Fractal::calculate_chance_suma() {
  chance_suma = 0;
  for (auto& it : branches) {
    chance_suma += it.chance;
  }
}

int Fractal::choose() const {
  double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * chance_suma;
  //std::cout << r << " " << chance_suma << std::endl;
  int j = 0;
  do {
    r -= branches[j].chance;
    j++;
  } while ((r >= 0) && (j <= branches.size()));
  j--;
  return j;
}

void Fractal::draw(Point2D pos) {
  Renderer::current()->set_offset(pos.x, pos.y);
  Point2D seed;
  int off_screen;
  for (int i = maxiter; i > 0; i--) {
    int r = choose();
    Point2D& vertex_pos = branches[r].pos;
    seed -= vertex_pos;
    seed = branches[r].transform.apply_transform(seed);
    seed += vertex_pos;
    if (Renderer::current()->put_pixel(seed.x, seed.y, colour)) {
      off_screen = 0;
    } else {
      off_screen++;
      if (off_screen > 500) {
        //The fractal is most likely off-screen, interrupt drawing.
        break;
      }
    }
    //Renderer::current()->fill_rect(seed.x, seed.y, seed.x+3, seed.y+3, Colour(0, 0, 0));
  }
}
