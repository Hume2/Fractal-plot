#include "fractal.h"

#include "matrix.h"
#include "point.h"
#include "../plot/colour.h"
#include "../plot/renderer.h"

Fractal::Fractal() :
  branches(),
  maxiter(9)
{

}

void Fractal::iterate(Point2D pos, Matrix2D matrix, int iter) {
  Point2D point_pos = matrix.apply_transform(pos);
  if (iter < maxiter) {
    for (auto& it : branches) {
      Matrix2D new_matrix = matrix * it;
      iterate(pos, new_matrix, iter + 1);
    }
  } else {
    Renderer::current()->put_pixel(point_pos.x, point_pos.y, Colour(0, 0, 0));
  }
}

void Fractal::draw(Point2D pos) {
  iterate(pos, Matrix2D(Matrix2D::TRANSLATE, pos.x, pos.y), 0);
}
