#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

#include "matrix.h"
#include "point.h"

class Fractal
{
  public:
    struct Branch {
      public:
        Branch(const Matrix2D transform_, const Point2D pos_, const double chance_ = 1.0f) :
          transform(transform_),
          pos(pos_),
          chance(chance_)
        { }

        Matrix2D transform;
        Point2D pos;
        double chance;
    };

    Fractal();

    int maxiter;
    std::vector<Branch> branches;

    void draw(Point2D pos);
    int choose() const;

    void calculate_chance_suma();

  private:
    double chance_suma;
};

#endif // FRACTAL_H
