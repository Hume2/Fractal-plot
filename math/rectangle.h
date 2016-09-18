#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"

class Rectangle
{
  public:
    Rectangle();
    Rectangle(const Point2D p1_, const Point2D p2_);
    Rectangle(const double x1, const double y1, const double x2, const double y2);

    void normalize();

    void set_size(const double width, const double height);
    void set_pos(const Point2D pos);

    Point2D get_center() const;
    double get_width() const;
    double get_height() const;

    Point2D p1, p2;
};

#endif // RECTANGLE_H
