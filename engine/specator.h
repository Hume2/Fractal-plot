#ifndef SPECATOR_H
#define SPECATOR_H

#include "../math/matrix.h"

class Point3D;

class Specator
{
  public:
    Specator();

    void update(/*int elapsed_time*/);

    void set_look_matrix(const Matrix3D matrix);
    void move(const Point3D shift);
    void shift(const Point3D shift);
    void set_pos(const Point3D pos);
    void turn_left(const float angle);
    void set_yaw(const float angle);
    void turn_up(const float angle);
    void set_pitch(const float angle);

    Point3D get_pos() const;
    Point3D get_aim_vector() const;
    double get_yaw() const;
    double get_pitch() const;

  private:
    Matrix3D look;
    double yaw, pitch;

    void recalculate_matrix();
};

#endif // SPECATOR_H
