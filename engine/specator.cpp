#include <math.h>

#include "specator.h"

#include "../math/point.h"

#include "../plot/renderer.h"

Specator::Specator() :
  look(),
  yaw(0),
  pitch(0)
{

}

void Specator::update() {
  Renderer::current()->set_transform_matrix(look);
}

void Specator::set_look_matrix(const Matrix3D matrix) {
  look = matrix;
}

void Specator::shift(const Point3D shift) {
  look.d -= shift.x;
  look.h -= shift.y;
  look.l -= shift.z;
}

void Specator::move(const Point3D shift) {
  look.add_transform(Matrix3D(Matrix3D::TRANSLATE, -shift.x, -shift.y, -shift.z));
}

void Specator::set_pos(const Point3D pos) {
  look.d = -pos.x;
  look.h = -pos.y;
  look.l = -pos.z;
}

void Specator::turn_left(const float angle) {
  yaw += angle;
  while (yaw > M_PI) {
    yaw -= 2 * M_PI;
  }
  while (yaw < -M_PI) {
    yaw += 2 * M_PI;
  }
  recalculate_matrix();
}

void Specator::turn_up(const float angle) {
  pitch += angle;
  if (pitch > M_PI_2) {
    pitch = M_PI_2;
  } else if (pitch < -M_PI_2) {
    pitch = -M_PI_2;
  }
  recalculate_matrix();
}

Point3D Specator::get_pos() const {
  return Point3D(-look.d, -look.h, -look.l);
}

Point3D Specator::get_aim_vector() const {
  return Point3D(cos(pitch) * cos(yaw), cos(pitch) * sin(yaw), sin(pitch));
}

double Specator::get_pitch() const {
  return pitch;
}

double Specator::get_yaw() const {
  return yaw;
}

void Specator::set_pitch(const float angle) {
  pitch = angle;
  recalculate_matrix();
}

void Specator::set_yaw(const float angle) {
  yaw = angle;
  recalculate_matrix();
}

void Specator::recalculate_matrix() {
  Point3D pos = get_pos();
  look = Matrix3D(Matrix3D::ROTATE, yaw, pitch, 0);
  set_pos(pos);
}
