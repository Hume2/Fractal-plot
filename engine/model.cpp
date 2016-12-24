#include <math.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "lisp_loader.h"
#include "model.h"

#include "../math/matrix.h"

Model::Transform::Transform(Type type_) :
  data(),
  modif(),
  type(type_)
{
  data.resize(get_count());
  modif.resize(get_count());
  for (int i = get_count() - 1; i >= 0; i--) {
    data[i] = 0;
    modif[i] = 0;
  }
}

Model::Transform::~Transform() {

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
  if (modifier == 0) {
    return base;
  }

  double rn = fmodf(rand(), modifier);
  if (rn < 0) {
    rn *= -1;
  }
  //std::cout << "base:" << base << " modifier:" << modifier << " result:" << (base+rn) << std::endl;
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
  pos(0, 0, 0),
  pos_m(0, 0, 0),
  c(0, 0, 0),
  c_m(0, 0, 0),
  chance(1),
  chance_m(0)
{

}

Model::Branch::~Branch() {

}

const Fractal3D::Branch Model::Branch::use_prototype() const {
  Matrix3D matrix;
  for (auto& it : transforms) {
    matrix.add_transform(it.get_matrix());
    //matrix *= it.get_matrix();
  }

  Colour colour(r(c.r, c_m.r), r(c.g, c_m.g), r(c.b, c_m.b));
  Point3D position(r(pos.x, pos_m.x), r(pos.y, pos_m.y), r(pos.z, pos_m.z));

  return Fractal3D::Branch(matrix, position, colour, r(chance, chance_m));
}

void Model::Branch::load_from_lisp(LispLoader &lisp) {
  std::string key;
  std::vector<float> array;

  while (!lisp.is_end()) {
    key = lisp.get_key();

    if (key == "chance") {
      lisp.get_num( &chance );
    } else if (key == "chance_modifier") {
      lisp.get_num( &chance_m );
    } else if (key == "pos") {
      lisp.get_array( &array );
      pos.x = array[0];
      pos.y = array[1];
      pos.z = array[2];
    } else if (key == "pos_modifier") {
      lisp.get_array( &array );
      pos_m.x = array[0];
      pos_m.y = array[1];
      pos_m.z = array[2];
    } else if (key == "colour") {
      lisp.get_array( &array );
      c.r = int(array[0]);
      c.g = int(array[1]);
      c.b = int(array[2]);
    } else if (key == "colour_modifier") {
      lisp.get_array( &array );
      c_m.r = int(array[0]);
      c_m.g = int(array[1]);
      c_m.b = int(array[2]);
    } else if (key == "transform") {
      load_transform_from_lisp(lisp);
    } else {
      lisp.go_up();
    }
  }

  lisp.go_up();
}

void Model::Branch::load_transform_from_lisp(LispLoader &lisp) {
  std::string key, type_s;
  std::vector<float> data, modif;
  Transform::Type type = Transform::MATRIX;

  while (!lisp.is_end()) {
    key = lisp.get_key();

    if (key == "type") {
      lisp.get_string( &type_s );

      if (type_s == "matrix") {
        type = Transform::MATRIX;
      } else if (type_s == "translate") {
        type = Transform::TRANSLATE;
      } else if (type_s == "rotate") {
        type = Transform::ROTATE;
      } else if (type_s == "scale") {
        type = Transform::SCALE;
      } else if (type_s == "shear") {
        type = Transform::SHEAR;
      } else {
        std::cout << "Error: unknown type of transform: " << type_s << std::endl;
      }

    } else if (key == "data") {
      lisp.get_array( &data );
    } else if (key == "modif") {
      lisp.get_array( &modif );
    } else {
      lisp.go_up();
    }
  }

  Transform t(type);

  for (int i = t.get_count() - 1; i >= 0; i--) {
    t.data[i] = data[i];
    t.modif[i] = modif[i];
  }

  transforms.push_back(t);

  lisp.go_up();
}

Model::Model() :
  maxiter(1000),
  offscreen_factor(100),
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

