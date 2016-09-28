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
  offscreen_factor(100),
  chance_suma()
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
  Colour colour;
  int off_screen;
  for (int i = maxiter; i > 0; i--) {
    int r = choose();
    colour.average(branches[r].colour);
    Point2D& vertex_pos = branches[r].pos;
    seed -= vertex_pos;
    seed = branches[r].transform.apply_transform(seed);
    seed += vertex_pos;
    if (Renderer::current()->put_pixel(seed.x, seed.y, colour)) {
      off_screen = 0;
    } else if (offscreen_factor >= 0) {
      off_screen++;
      if (off_screen > 100) {
        //The fractal is most likely off-screen, interrupt drawing.
        break;
      }
    }
  }
}

//------------------------------------------------------------------------------
// Fractal 3D
//------------------------------------------------------------------------------

Fractal3D::Fractal3D() :
  pos(),
  branches(),
  maxiter(1000),
  offscreen_factor(100),
  chance_suma()
{

}

double Fractal3D::get_chance(int id) const {
  return branches[id].chance / (branches[id].pos.z + pos.z) * 100;
}

void Fractal3D::calculate_chance_suma() {
  chance_suma = 0;
  for (int i = branches.size() - 1; i >= 0; i--) {
    chance_suma += get_chance(i);
  }
}

int Fractal3D::choose() const {
  double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * chance_suma;
  int j = 0;
  do {
    r -= get_chance(j);
    j++;
  } while ((r >= 0) && (j <= branches.size()));
  j--;
  return j;
}

void Fractal3D::draw() {
  calculate_chance_suma();
  Point3D seed;
  Colour colour;
  int off_screen;
  float distance_factor = 200.0f / pos.z; // Draw less points when farther
  distance_factor *= distance_factor;
  for (int i = maxiter * distance_factor; i > 0; i--) {
    int r = choose();
    colour.average(branches[r].colour);
    Point3D& vertex_pos = branches[r].pos;
    seed -= vertex_pos;
    seed = branches[r].transform.apply_transform(seed);
    seed += vertex_pos;
    if (Renderer::current()->put_pixel(seed + pos, colour)) {
      off_screen = 0;
    } else if (offscreen_factor >= 0) {
      off_screen++;
      if (off_screen > 100) {
        //The fractal is most likely off-screen, interrupt drawing.
        break;
      }
    }
  }
}
