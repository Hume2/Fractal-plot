#include <algorithm>
#include <stdio.h>

#include "colour.h"

Colour::Colour() :
  r(0),
  g(0),
  b(0)
{

}

Colour::Colour(unsigned char r_, unsigned char g_, unsigned char b_) :
  r(r_),
  g(g_),
  b(b_)
{

}

bool Colour::operator ==(const Colour a) const {
  return r == a.r && g == a.g && b == a.b;
}

bool Colour::operator !=(const Colour a) const {
  return r != a.r || g != a.g || b != a.b;
}

Colour Colour::operator *(const Colour a) const {
  float rf = a.r / 255.0f;
  float gf = a.g / 255.0f;
  float bf = a.b / 255.0f;
  return Colour(r * rf, g * gf, b * bf);
}

Colour& Colour::operator *=(const Colour a) {
  float rf = a.r / 255.0f;
  float gf = a.g / 255.0f;
  float bf = a.b / 255.0f;
  r *= rf;
  g *= gf;
  b *= bf;
  return *this;
}

void Colour::average(const Colour a) {
  r = (r + a.r) / 2;
  g = (g + a.g) / 2;
  b = (b + a.b) / 2;
}
