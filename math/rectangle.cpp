#include <algorithm>
#include <stdio.h>

#include "../main.h"

#include "rectangle.h"

#include "../plot/renderer.h"

Rectangle::Rectangle() :
  p1(0, 0),
  p2(0, 0)
{

}

Rectangle::Rectangle(const Point2D p1_, const Point2D p2_) :
  p1(p1_),
  p2(p2_)
{

}

Rectangle::Rectangle(const double x1, const double y1, const double x2, const double y2) :
  p1(x1, y1),
  p2(x2, y2)
{

}

void Rectangle::normalize() {
  if (p1.x > p2.x) {
    std::swap(p1.x, p2.x);
  }

  if (p1.y > p2.y) {
    std::swap(p1.y, p2.y);
  }
}

void Rectangle::set_size(const double width, const double height) {
  p2.x = p1.x + width;
  p2.y = p1.y + height;
}

void Rectangle::set_pos(const Point2D pos) {
  Point2D shift = pos - p1;
  p2 += shift;
  p1 = pos;
}

void Rectangle::adjust_point(const Point2D p) {
  if (p.x < p1.x) {
    p1.x = p.x;
  } else if (p.x > p2.x) {
    p2.x = p.x;
  }

  if (p.y < p1.y) {
    p1.y = p.y;
  } else if (p.y > p2.y) {
    p2.y = p.y;
  }
}

double Rectangle::get_width() const {
  return p2.x - p1.x;
}

double Rectangle::get_height() const {
  return p2.y - p1.y;
}

Point2D Rectangle::get_center() const {
  return (p1 + p2) / 2;
}

bool Rectangle::is_on_screen() const {
  Point2D offset = Renderer::current()->get_offset();
  return p1.x < SCREEN_WIDTH - offset.x  && p2.x >= -offset.x &&
         p1.y < SCREEN_HEIGHT - offset.y && p2.y >= -offset.y;
}
