#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string>

class Point2D;
class Point3D;

class Matrix2D
{
  public:
    enum Method{TRANSLATE, SCALE, SHEAR, ROTATE};

    /**
     * TRANSLATE (X, Y)
     * SCALE (X, Y)
     * SHEAR (X, Y)
     * ROTATE (A, 0)
     */

    Matrix2D();
    Matrix2D(const double a_, const double b_, const double c_,
             const double d_, const double e_, const double f_,
             const double g_, const double h_, const double i_);
    Matrix2D(Method method, const double x, const double y);

    double a, b, c;
    double d, e, f;
    double g, h, i;

    Matrix2D operator+(const Matrix2D x) const;
    Matrix2D operator-() const;
    Matrix2D operator-(const Matrix2D x) const;
    Matrix2D operator*(const Matrix2D x) const;

    bool operator==(const Matrix2D x) const;
    bool operator!=(const Matrix2D x) const;

    Matrix2D& operator+=(const Matrix2D x);
    Matrix2D& operator-=(const Matrix2D x);
    Matrix2D& operator*=(const Matrix2D x);

    std::string to_string() const;

    void add_transform(const Matrix2D x);
    Point2D apply_transform(const Point2D x) const;
};

class Matrix3D
{
  public:
    enum Method{TRANSLATE, SCALE, SHEAR_XY, SHEAR_XZ, SHEAR_YZ, ROTATE};

    /**
     * TRANSLATE (X, Y, Z)
     * SCALE (X, Y, Z)
     * SHEAR_XY (X, Y, 0)
     * SHEAR_XZ (X, Z, 0)
     * SHEAR_YZ (Y, Z, 0)
     * ROTATE (A, B, G) jaw, pitch and roll
     */

    Matrix3D();
    Matrix3D(const double a_, const double b_, const double c_, const double d_,
             const double e_, const double f_, const double g_, const double h_,
             const double i_, const double j_, const double k_, const double l_,
             const double m_, const double n_, const double o_, const double p_);
    Matrix3D(Method method, const double x, const double y, const double z);

    double a, b, c, d;
    double e, f, g, h;
    double i, j, k, l;
    double m, n, o, p;

    Matrix3D operator+(const Matrix3D x) const;
    Matrix3D operator-() const;
    Matrix3D operator-(const Matrix3D x) const;
    Matrix3D operator*(const Matrix3D x) const;

    bool operator==(const Matrix3D x) const;
    bool operator!=(const Matrix3D x) const;

    Matrix3D& operator+=(const Matrix3D x);
    Matrix3D& operator-=(const Matrix3D x);
    Matrix3D& operator*=(const Matrix3D x);

    std::string to_string() const;

    void add_transform(const Matrix3D x);
    Point3D apply_transform(const Point3D x) const;
};

#endif // MATRIX_H
