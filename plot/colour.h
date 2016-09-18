#ifndef COLOUR_H
#define COLOUR_H


class Colour
{
  public:
    Colour();
    Colour(unsigned char r_, unsigned char g_, unsigned char b_);

    bool operator==(const Colour a) const;
    bool operator!=(const Colour a) const;

    unsigned char r, g, b;
};

#endif // COLOUR_H
