#include <math.h>

#include "specator.h"

#include "../plot/renderer.h"

Specator::Specator() :
  look(),
  yaw(0),
  pitch(0),
  pos(Point3D(0, 0, 0))
{

}

void Specator::update() {
  Renderer::current()->set_transform_matrix(look);
}

void Specator::set_look_matrix(const Matrix3D matrix) {
  look = matrix;
}

void Specator::shift(const Point3D shift) {
  pos += shift;
  recalculate_matrix();
}

void Specator::move_forwards(const double shift) {
  Point3D aim = get_aim_vector();
  pos.x += aim.x * shift;
  pos.y += aim.y * shift;
  pos.z += aim.z * shift;
  recalculate_matrix();
}

void Specator::move_sidewards(const double shift) {
  Point3D aim = get_side_vector();
  pos.x += aim.x * shift;
  pos.y += aim.y * shift;
  pos.z += aim.z * shift;
  recalculate_matrix();
}

void Specator::set_pos(const Point3D pos_) {
  pos = pos_;
  recalculate_matrix();
}

void Specator::turn_right(const float angle) {
  yaw += angle;
  while (yaw > M_PI) {
    yaw -= 2 * M_PI;
  }
  while (yaw < -M_PI) {
    yaw += 2 * M_PI;
  }
  recalculate_matrix();
}

void Specator::turn_down(const float angle) {
  pitch += angle;
  if (pitch > M_PI_2) {
    pitch = M_PI_2;
  } else if (pitch < -M_PI_2) {
    pitch = -M_PI_2;
  }
  recalculate_matrix();
}

Point3D Specator::get_pos() const {
  return pos;
}

Point3D Specator::get_aim_vector() const {
  return Point3D(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
}

Point3D Specator::get_side_vector() const {
  return Point3D(cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw));
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
  look = Matrix3D(Matrix3D::ROTATE, -yaw, -pitch, 0) *
         Matrix3D(Matrix3D::TRANSLATE, -pos.x, -pos.y, -pos.z);
  //look = Matrix3D(Matrix3D::TRANSLATE, -pos.x, -pos.y, -pos.z) *
  //       Matrix3D(Matrix3D::ROTATE, -yaw, -pitch, 0);
}
