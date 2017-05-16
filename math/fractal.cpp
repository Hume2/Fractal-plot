#include <algorithm>
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

void Fractal3D::precalculate_branches() {
  chance_suma = 0;
  for (int id = branches.size() - 1; id >= 0; id--) {
    Point3D p = branches[id].pos + pos;
    branches[id].real_transform = Matrix3D(Matrix3D::TRANSLATE, p.x, p.y, p.z) *
                                  branches[id].transform *
                                  Matrix3D(Matrix3D::TRANSLATE, -p.x, -p.y, -p.z);

    Point3D rel_point = Renderer::current()->get_transform_matrix().apply_transform(p);
    if (rel_point.z > 0.01f) {
      branches[id].real_chance = branches[id].chance / rel_point.z * 100;
    } else {
      branches[id].real_chance = branches[id].chance;
    }
    chance_suma += branches[id].real_chance;
    //chance_suma += branches[id].chance;
  }
}

int Fractal3D::choose() const {
  double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * chance_suma;
  int j = 0;
  do {
    r -= branches[j].real_chance;
    j++;
  } while ((r >= 0) && (j <= branches.size()));
  j--;
  return j;
}

void Fractal3D::draw() {
  precalculate_branches();
  Point3D seed;
  Colour colour;
  int off_screen = 0;
  Point3D rel_point = Renderer::current()->get_transform_matrix().apply_transform(pos);
  //float rel_z = pos.z - Renderer::relative_pos.z;
  float distance_factor = (rel_point.z > 0.1f) ? (1.0f / rel_point.z) : 10.0f; // Draw less points when farther
  //distance_factor *= distance_factor;
  for (int i = maxiter  * distance_factor; i > 0; i--) {
    int r = choose();
    colour.average(branches[r].colour);
    /*Point3D& vertex_pos = branches[r].real_pos;
    seed -= vertex_pos;
    seed = branches[r].transform.apply_transform(seed);
    seed += vertex_pos;*/
    seed = branches[r].real_transform.apply_transform(seed);
    if (Renderer::current()->put_pixel(seed, colour)) {
      off_screen = 0;
    } else {
      off_screen++;
      if (off_screen > offscreen_factor) {
        //The fractal is most likely off-screen, interrupt drawing.
        break;
      }
    }
  }
}
