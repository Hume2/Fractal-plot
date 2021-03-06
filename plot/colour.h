#ifndef COLOUR_H
#define COLOUR_H

#include <stdio.h>
#include <iostream>

class Colour
{
  public:
    Colour();
    Colour(unsigned char r_, unsigned char g_, unsigned char b_);

    bool operator==(const Colour a) const;
    bool operator!=(const Colour a) const;

    Colour operator*(const Colour a) const;
    Colour& operator*=(const Colour a);

    void average(const Colour a);

    void save(FILE* f);
    void load(FILE* f);

    unsigned char r, g, b;
};

#endif // COLOUR_H
