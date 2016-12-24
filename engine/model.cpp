#include <math.h>
#include <time.h>
#include <cstdlib>
#include <ctime>

#include "model.h"

#include "../math/matrix.h"

Model::Transform::Transform(Type type_) :
  data(),
  modif(),
  type(type_)
{
  data = new float[get_count()];
  modif = new float[get_count()];
}

Model::Transform::~Transform() {
  delete[] data;
  delete[] modif;
}

int Model::Transform::get_count() const {
  switch (type) {
    case MATRIX: return 16;
    case TRANSLATE: return 3;
    case ROTATE: return 3;
    case SCALE: return 3;
    case SHEAR: return 6;
  }
}

double Model::r(const double base, const double modifier) {
  double rn = fmodf(rand(), modifier);
  if (rn < 0) {
    rn *= -1;
  }
  return base + rn;
}

Matrix3D Model::Transform::get_matrix() const {
  switch (type) {
    case MATRIX:
      return Matrix3D(r(data[ 0], modif[ 0]), r(data[ 1], modif[ 1]), r(data[ 2], modif[ 2]), r(data[ 3], modif[ 3]),
                      r(data[ 4], modif[ 4]), r(data[ 5], modif[ 5]), r(data[ 6], modif[ 6]), r(data[ 7], modif[ 7]),
                      r(data[ 8], modif[ 8]), r(data[ 9], modif[ 9]), r(data[10], modif[10]), r(data[11], modif[11]),
                      r(data[12], modif[12]), r(data[13], modif[13]), r(data[14], modif[14]), r(data[15], modif[15]));
    case TRANSLATE:
      return Matrix3D(Matrix3D::TRANSLATE, r(data[0], modif[0]), r(data[1], modif[1]), r(data[2], modif[2]));
    case ROTATE:
      return Matrix3D(Matrix3D::ROTATE, r(data[0], modif[0]), r(data[1], modif[1]), r(data[2], modif[2]));
    case SCALE:
      return Matrix3D(Matrix3D::SCALE, r(data[0], modif[0]), r(data[1], modif[1]), r(data[2], modif[2]));
    case SHEAR:
      return Matrix3D(                   1, r(data[0], modif[0]), r(data[2], modif[2]), 0,
                      r(data[1], modif[1]),                    1, r(data[4], modif[4]), 0,
                      r(data[3], modif[3]), r(data[5], modif[5]),                    1, 0,
                                         0,                    0,                    0, 1);
  }
}

Model::Branch::Branch() :
  transforms(),
  pos(),
  pos_m(),
  c(),
  c_m(),
  chance(),
  chance_m()
{

}

Model::Branch::~Branch() {

}

const Fractal3D::Branch Model::Branch::use_prototype() const {
  Matrix3D matrix;
  for (auto& it : transforms) {
    matrix.add_transform(it.get_matrix());
  }

  Colour colour(r(c.r, c_m.r), r(c.g, c_m.g), r(c.b, c_m.b));
  Point3D position(r(pos.x, pos_m.x), r(pos.y, pos_m.y), r(pos.z, pos_m.z));

  return Fractal3D::Branch(matrix, position, colour, r(chance, chance_m));
}

Model::Model() :
  maxiter(),
  offscreen_factor(),
  branches()
{

}

Model::~Model() {

}

Fractal3D Model::use_prototype() const {
  Fractal3D result;
  result.maxiter = maxiter;
  result.offscreen_factor = offscreen_factor;

  for (auto& it : branches) {
    result.branches.push_back( it.use_prototype() );
  }

  return result;
}

