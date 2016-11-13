#ifndef SPECATOR_H
#define SPECATOR_H

#include "../math/matrix.h"
#include "../math/point.h"

class Specator
{
  public:
    Specator();

    void update(/*int elapsed_time*/);

    void set_look_matrix(const Matrix3D matrix);
    void move_forwards(const double shift);
    void move_sidewards(const double shift);
    void shift(const Point3D shift);
    void set_pos(const Point3D pos_);
    void turn_right(const float angle);
    void set_yaw(const float angle);
    void turn_down(const float angle);
    void set_pitch(const float angle);

    Point3D get_pos() const;
    Point3D get_aim_vector() const;
    Point3D get_side_vector() const;
    double get_yaw() const;
    double get_pitch() const;

  private:
    Matrix3D look;
    double yaw, pitch;
    Point3D pos;

    void recalculate_matrix();
};

#endif // SPECATOR_H
