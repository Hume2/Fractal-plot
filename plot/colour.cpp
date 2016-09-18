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
