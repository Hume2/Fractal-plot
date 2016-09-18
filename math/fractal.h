#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

class Matrix2D;
class Point2D;

class Fractal
{
  public:
    Fractal();

    int maxiter;
    std::vector<Matrix2D> branches;

    void draw(Point2D pos);

  private:
    void iterate(Point2D pos, Matrix2D matrix, int iter);
};

#endif // FRACTAL_H
