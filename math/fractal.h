#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

#include "matrix.h"
#include "point.h"

class Fractal
{
  public:
    Fractal();

    int maxiter;
    std::vector<Matrix2D> branches;

    void draw(Point2D pos);

  private:
    void iterate(Point2D pos, Point2D point_pos, Matrix2D matrix, int iter);

    struct BranchRequest {
      public:
        BranchRequest(Matrix2D transform_, Point2D pos_) :
          transform(transform_),
          pos(pos_)
        { }

        Matrix2D transform;
        Point2D pos;
    };
};

#endif // FRACTAL_H
