#include <stdio.h>
#include <iostream>

#include "math/point.h"
#include "math/matrix.h"

int main(int argc, char *argv[])
{
  Point3D point(5, 2, 3);
  Matrix3D matrix(Matrix3D::ROTATE, 1, 1, 1);
  matrix.add_transform(Matrix3D(Matrix3D::TRANSLATE, 3, 3, 3));
  point = matrix.apply_transform(point);

  std::cout << point.to_string() << std::endl;
  return 0;
}

