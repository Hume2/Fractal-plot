#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

#include "matrix.h"
#include "point.h"

#include "../plot/colour.h"

class Fractal
{
  public:
    struct Branch {
      public:
        Branch(const Matrix2D transform_, const Point2D pos_,
               const Colour c = Colour(0, 0, 0), const double chance_ = 1.0f) :
          transform(transform_),
          pos(pos_),
          chance(chance_),
          colour(c)
        { }

        Matrix2D transform;
        Point2D pos;
        double chance;
        Colour colour;
    };

    Fractal();

    int maxiter;
    int offscreen_factor;
    std::vector<Branch> branches;

    void draw(Point2D pos);

    int choose() const;
    void calculate_chance_suma();

  private:
    double chance_suma;
};

class Fractal3D
{
  public:
    struct Branch {
      public:
        Branch(const Matrix3D transform_, const Point3D pos_,
               const Colour c = Colour(0, 0, 0), const double chance_ = 1.0f) :
          transform(transform_),
          pos(pos_),
          chance(chance_),
          colour(c)
        { }

        Matrix3D transform;
        Point3D pos;
        double chance;
        Colour colour;
    };

    Fractal3D();

    Point3D pos;

    int maxiter;
    int offscreen_factor;
    std::vector<Branch> branches;

    void draw();

    double get_chance(int id) const;
    int choose() const;
    void calculate_chance_suma();

  private:
    double chance_suma;
};

#endif // FRACTAL_H
