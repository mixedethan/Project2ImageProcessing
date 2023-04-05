#pragma once
#include "Pixel.h"
#include "Header.h"
#include <vector>
#include <string>
using namespace std;

struct Image{
    Header _header;
    string _name;
    vector<Pixel> _pixelData;

    //Constructors
    Image(){}
    Image(string name, Header &header, vector<Pixel> &imageData);

    //Overloaded operators
    Image& operator = (Image &image);
    bool operator == (const Image &rhs) const;
    Image operator*(const Image &rhs); //Multiply
    Image operator/(const Image &rhs); //Divide
    Image operator-(const Image &rhs); //Subtract
    Image operator|(Image &rhs); //Screen

    //Image adjustments
    Image addBlue(const int &num);
    Image addGreen(const int &num);
    Image addRed(const int &num);
    Image multiplyBlue(const int &times);
    Image multiplyGreen(const int &times);
    Image multiplyRed(const int &times);
    Image separateBlue();
    Image separateGreen();
    Image separateRed();
    Image rotate180();

};