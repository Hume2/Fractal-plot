#include <stdio.h>
#include <iostream>

#include "fractal.h"

#include "rectangle.h"
#include "../plot/colour.h"
#include "../plot/renderer.h"

Fractal::Fractal() :
  branches(),
  maxiter(5)
{

}

void Fractal::iterate(Point2D pos, Point2D point_pos, Matrix2D matrix, int iter) {
  //Point2D point_pos = matrix.apply_transform(pos);
  Rectangle point_rect(point_pos, point_pos);
  std::vector<BranchRequest> branch_requests;
  if (iter < maxiter) {
    for (auto& it : branches) {
      Matrix2D new_matrix = matrix * it;
      Point2D new_pos = new_matrix.apply_transform(pos);
      branch_requests.push_back(BranchRequest(new_matrix, new_pos));
      point_rect.adjust_point(new_pos);
      //iterate(pos, new_matrix.apply_transform(pos), new_matrix, iter + 1);
    }
  }

  if (iter < maxiter && point_rect.get_width() > 1.0f && point_rect.get_height() > 1.0f) {
    for (auto& it : branch_requests) {
      iterate(pos, it.pos, it.transform, iter + 1);
      //Renderer::current()->fill_rect(it.pos.x, it.pos.y, it.pos.x, it.pos.y, Colour(255, 0, 0));
    }
  } else {
    if (point_rect.is_on_screen()) {
      Renderer::current()->fill_rect(point_rect.p1.x, point_rect.p1.y, point_rect.p2.x, point_rect.p2.y,
                                     Colour(0, 0, 0));
      //Renderer::current()->put_pixel(point_pos.x, point_pos.y, Colour(0, 0, 0));
    }
  }
}

void Fractal::draw(Point2D pos) {
  Renderer::current()->set_offset(pos.x, pos.y);
  Matrix2D initial_matrix = Matrix2D(Matrix2D::TRANSLATE, 0, 0);
  iterate(Point2D(0, 0), initial_matrix.apply_transform(pos), initial_matrix, 0);
}
