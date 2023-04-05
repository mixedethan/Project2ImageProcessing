#pragma once

struct Pixel{
    unsigned char _blue;
    unsigned char _green;
    unsigned char _red;
    float _floatBlue;
    float _floatGreen;
    float _floatRed;

    Pixel(){}

    Pixel(unsigned char red, unsigned char green, unsigned char blue);

    bool operator==(const Pixel &rhs) const;

    Pixel operator*(const Pixel &rhs);

    Pixel operator-(const Pixel &rhs);

    Pixel operator/(const Pixel &rhs);



};
