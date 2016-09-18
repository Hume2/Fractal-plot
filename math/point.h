#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <string>

class Point3D;

class Point2D
{
  public:
    Point2D();
    Point2D(const double x_, const double y_);
    Point2D(const Point3D p);

    double x, y;

    Point2D operator+(const Point2D a) const;
    Point2D operator-() const;
    Point2D operator-(const Point2D a) const;

    bool operator==(const Point2D a) const;
    bool operator!=(const Point2D a) const;

    Point2D& operator+=(const Point2D a);
    Point2D& operator-=(const Point2D a);

    std::string to_string() const;
};

class Point3D
{
  public:
    Point3D();
    Point3D(const double x_, const double y_, const double z_);
    Point3D(const Point2D p);

    double x, y, z;

    Point3D operator+(const Point3D a) const;
    Point3D operator-() const;
    Point3D operator-(const Point3D a) const;

    bool operator==(const Point3D a) const;
    bool operator!=(const Point3D a) const;

    Point3D& operator+=(const Point3D a);
    Point3D& operator-=(const Point3D a);

    std::string to_string() const;
};

#endif // POINT_H
