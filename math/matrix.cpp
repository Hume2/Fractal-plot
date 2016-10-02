#include <assert.h>
#include <math.h>

#include "matrix.h"

#include "point.h"

Matrix2D::Matrix2D() :
  a(1), b(0), c(0),
  d(0), e(1), f(0),
  g(0), h(0), i(1)
{

}

Matrix2D::Matrix2D(const double a_, const double b_, const double c_,
                   const double d_, const double e_, const double f_,
                   const double g_, const double h_, const double i_) :
  a(a_), b(b_), c(c_),
  d(d_), e(e_), f(f_),
  g(g_), h(h_), i(i_)
{

}

Matrix2D::Matrix2D(Method method, const double x, const double y) :
  a(), b(), c(),
  d(), e(), f(),
  g(), h(), i()
{
  switch (method) {
    case TRANSLATE:
      a = 1; b = 0; c = x;
      d = 0; e = 1; f = y;
      g = 0; h = 0; i = 1;
      break;
    case SCALE:
      a = x; b = 0; c = 0;
      d = 0; e = y; f = 0;
      g = 0; h = 0; i = 1;
      break;
    case SHEAR:
      a = 1; b = x; c = 0;
      d = y; e = 1; f = 0;
      g = 0; h = 0; i = 1;
      break;
    case ROTATE:
      a =  cos(x); b = sin(x); c = 0;
      d = -sin(x); e = cos(x); f = 0;
      g =       0; h =      0; i = 1;
      break;
    default:
      assert(!"Invalid transformation method.");
      break;
  }
}

Matrix2D Matrix2D::operator +(const Matrix2D x) const {
  return Matrix2D(a + x.a, b + x.b, c + x.c,
                  d + x.d, e + x.e, f + x.f,
                  g + x.g, h + x.h, i + x.i);
}

Matrix2D Matrix2D::operator -() const {
  return Matrix2D(-a, -b, -c,
                  -d, -e, -f,
                  -g, -h, -i);
}

Matrix2D Matrix2D::operator -(const Matrix2D x) const {
  return Matrix2D(a - x.a, b - x.b, c - x.c,
                  d - x.d, e - x.e, f - x.f,
                  g - x.g, h - x.h, i - x.i);
}

Matrix2D Matrix2D::operator *(const Matrix2D x) const {
  return Matrix2D(a*x.a + b*x.d + c*x.g, a*x.b + b*x.e + c*x.h, a*x.c + b*x.f + c*x.i,
                  d*x.a + e*x.d + f*x.g, d*x.b + e*x.e + f*x.h, d*x.c + e*x.f + f*x.i,
                  g*x.a + h*x.d + i*x.g, g*x.b + h*x.e + i*x.h, g*x.c + h*x.f + i*x.i);
}

std::string Matrix2D::to_string() const {
  return "[" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ",\n" +
               std::to_string(d) + ", " + std::to_string(e) + ", " + std::to_string(f) + ",\n" +
               std::to_string(g) + ", " + std::to_string(h) + ", " + std::to_string(i) + "]";
}

bool Matrix2D::operator ==(const Matrix2D x) const {
  return a == x.a && b == x.b && c == x.c &&
         d == x.d && e == x.e && f == x.f &&
         g == x.g && h == x.h && i == x.i;
}

bool Matrix2D::operator !=(const Matrix2D x) const {
  return a != x.a || b != x.b || c != x.c ||
         d != x.d || e != x.e || f != x.f ||
         g != x.g || h != x.h || i != x.i;
}

Matrix2D& Matrix2D::operator +=(const Matrix2D x) {
  a += x.a; b += x.b; c += x.c;
  d += x.d; e += x.e; f += x.f;
  g += x.g; h += x.h; i += x.i;
  return *this;
}

Matrix2D& Matrix2D::operator -=(const Matrix2D x) {
  a -= x.a; b -= x.b; c -= x.c;
  d -= x.d; e -= x.e; f -= x.f;
  g -= x.g; h -= x.h; i -= x.i;
  return *this;
}

Matrix2D& Matrix2D::operator *=(const Matrix2D x) {
  *this = *this * x;
  return *this;
}

void Matrix2D::add_transform(const Matrix2D x) {
  *this = x * *this;
}

Point2D Matrix2D::apply_transform(const Point2D x) const {
  return Point2D(a*x.x + b*x.y + c, d*x.x + e*x.y + f);
}

//------------------------------------------------------------------------------
// Matrix3D
//------------------------------------------------------------------------------

Matrix3D::Matrix3D() :
  a(1), b(0), c(0), d(0),
  e(0), f(1), g(0), h(0),
  i(0), j(0), k(1), l(0),
  m(0), n(0), o(0), p(1)
{

}

Matrix3D::Matrix3D(const double a_, const double b_, const double c_, const double d_,
                   const double e_, const double f_, const double g_, const double h_,
                   const double i_, const double j_, const double k_, const double l_,
                   const double m_, const double n_, const double o_, const double p_) :
  a(a_), b(b_), c(c_), d(d_),
  e(e_), f(f_), g(g_), h(h_),
  i(i_), j(j_), k(k_), l(l_),
  m(m_), n(n_), o(o_), p(p_)
{

}

Matrix3D::Matrix3D(Method method, const double x, const double y, const double z) :
  a(), b(), c(), d(),
  e(), f(), g(), h(),
  i(), j(), k(), l(),
  m(), n(), o(), p()
{
  switch (method) {
    case TRANSLATE:
      a = 1; b = 0; c = 0; d = x;
      e = 0; f = 1; g = 0; h = y;
      i = 0; j = 0; k = 1; l = z;
      m = 0; n = 0; o = 0; p = 1;
      break;
    case SCALE:
      a = x; b = 0; c = 0; d = 0;
      e = 0; f = y; g = 0; h = 0;
      i = 0; j = 0; k = z; l = 0;
      m = 0; n = 0; o = 0; p = 1;
      break;
    case SHEAR_XY:
      a = 1; b = x; c = 0; d = 0;
      e = y; f = 1; g = 0; h = 0;
      i = 0; j = 0; k = 1; l = 0;
      m = 0; n = 0; o = 0; p = 1;
      break;
    case SHEAR_XZ:
      a = 1; b = 0; c = x; d = 0;
      e = 0; f = 1; g = 0; h = 0;
      i = y; j = 0; k = 1; l = 0;
      m = 0; n = 0; o = 0; p = 1;
      break;
    case SHEAR_YZ:
      a = 1; b = 0; c = 0; d = 0;
      e = 0; f = 1; g = x; h = 0;
      i = 0; j = y; k = 1; l = 0;
      m = 0; n = 0; o = 0; p = 1;
      break;
    case ROTATE:
      a =  cos(z); b = sin(z); c =      0; d = 0;
      e = -sin(z); f = cos(z); g =      0; h = 0;
      i =       0; j =      0; k =      1; l = 0;
      m =       0; n =      0; o =      0; p = 1;
      add_transform(Matrix3D(
         1,       0,      0, 0,
         0,  cos(y), sin(y), 0,
         0, -sin(y), cos(y), 0,
         0,       0,      0, 1));
      add_transform(Matrix3D(
         cos(x), 0, sin(x), 0,
              0, 1,      0, 0,
        -sin(x), 0, cos(x), 0,
              0, 0,      0, 1));
      break;
    default:
      assert(!"Invalid transformation method.");
      break;
  }
}

Matrix3D Matrix3D::operator +(const Matrix3D x) const {
  return Matrix3D(a + x.a, b + x.b, c + x.c, d + x.d,
                  e + x.e, f + x.f, g + x.g, h + x.h,
                  i + x.i, j + x.j, k + x.k, l + x.l,
                  m + x.m, n + x.n, o + x.o, p + x.p);
}

Matrix3D Matrix3D::operator -() const {
  return Matrix3D(-a, -b, -c, -d,
                  -e, -f, -g, -h,
                  -i, -j, -k, -l,
                  -m, -n, -o, -p);
}

Matrix3D Matrix3D::operator -(const Matrix3D x) const {
  return Matrix3D(a - x.a, b - x.b, c - x.c, d - x.d,
                  e - x.e, f - x.f, g - x.g, h - x.h,
                  i - x.i, j - x.j, k - x.k, l - x.l,
                  m - x.m, n - x.n, o - x.o, p - x.p);
}

Matrix3D Matrix3D::operator *(const Matrix3D x) const {
  return Matrix3D(a*x.a + b*x.e + c*x.i + d*x.m, a*x.b + b*x.f + c*x.j + d*x.n, a*x.c + b*x.g + c*x.k + d*x.o, a*x.d + b*x.h + c*x.l + d*x.p,
                  e*x.a + f*x.e + g*x.i + h*x.m, e*x.b + f*x.f + g*x.j + h*x.n, e*x.c + f*x.g + g*x.k + h*x.o, e*x.d + f*x.h + g*x.l + h*x.p,
                  i*x.a + j*x.e + k*x.i + l*x.m, i*x.b + j*x.f + k*x.j + l*x.n, i*x.c + j*x.g + k*x.k + l*x.o, i*x.d + j*x.h + k*x.l + l*x.p,
                  m*x.a + n*x.e + o*x.i + p*x.m, m*x.b + n*x.f + o*x.j + p*x.n, m*x.c + n*x.g + o*x.k + p*x.o, m*x.d + n*x.h + o*x.l + p*x.p);
}

std::string Matrix3D::to_string() const {
  return "[" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ", " + std::to_string(d) + ",\n" +
               std::to_string(e) + ", " + std::to_string(f) + ", " + std::to_string(g) + ", " + std::to_string(h) + ",\n" +
               std::to_string(i) + ", " + std::to_string(j) + ", " + std::to_string(k) + ", " + std::to_string(l) + ",\n" +
               std::to_string(m) + ", " + std::to_string(n) + ", " + std::to_string(o) + ", " + std::to_string(p) + "]";
}

bool Matrix3D::operator ==(const Matrix3D x) const {
  return a == x.a && b == x.b && c == x.c && d == x.d &&
         e == x.e && f == x.f && g == x.g && h == x.h &&
         i == x.i && j == x.j && k == x.k && l == x.l &&
         m == x.m && n == x.n && o == x.o && p == x.p;
}

bool Matrix3D::operator !=(const Matrix3D x) const {
  return a != x.a || b != x.b || c != x.c || d != x.d ||
         e != x.e || f != x.f || g != x.g || h != x.h ||
         i != x.i || j != x.j || k != x.k || l != x.l ||
         m != x.m || n != x.n || o != x.o || p != x.p;
}

Matrix3D& Matrix3D::operator +=(const Matrix3D x) {
  a += x.a; b += x.b; c += x.c; d += x.d;
  e += x.e; f += x.f; g += x.g; h += x.h;
  i += x.i; j += x.j; k += x.k; l += x.l;
  m += x.m; n += x.n; o += x.o; p += x.p;
  return *this;
}

Matrix3D& Matrix3D::operator -=(const Matrix3D x) {
  a -= x.a; b -= x.b; c -= x.c; d -= x.d;
  e -= x.e; f -= x.f; g -= x.g; h -= x.h;
  i -= x.i; j -= x.j; k -= x.k; l -= x.l;
  m -= x.m; n -= x.n; o -= x.o; p -= x.p;
  return *this;
}

Matrix3D& Matrix3D::operator *=(const Matrix3D x) {
  *this = *this * x;
  return *this;
}

void Matrix3D::add_transform(const Matrix3D x) {
  *this = x * *this;
}

Point3D Matrix3D::apply_transform(const Point3D x) const {
  return Point3D(a*x.x + b*x.y + c*x.z + d,
                 e*x.x + f*x.y + g*x.z + h,
                 i*x.x + j*x.y + k*x.z + l);
}
