#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Header{
    char _idLength;
    char _colorMapType;
    char _imageType;
    short _colorMapOrigin;
    short _colorMapLength;
    char _colorMapDepth;
    short _xOrigin;
    short _yOrigin;
    short _width;
    short _height;
    char _pixelDepth;
    char _imageDescriptor;
    
/*
    void printHeader(){
        cout << (int)idLength  << endl << (int)colorMapType << endl << (int)imageType <<
        endl << colorMapOrigin << endl << colorMapLength << endl << (int)colorMapDepth
        << endl << xOrigin << endl << yOrigin << endl << width << endl << height << endl << (int)pixelDepth  << endl << (int)imageDescriptor << endl;
    }
*/
};