#include "Pixel.h"
#include <vector>

//FINISHED

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue){
    _blue = blue;
    _green = green;
    _red = red;
    _floatBlue = (float)blue / 255;
    _floatGreen = (float)green / 255;
    _floatRed = (float)red / 255;
}

bool Pixel::operator==(const Pixel &rhs) const{
    if(_blue == rhs._blue && _green == rhs._green && _red == rhs._red)
    {
        return true;
    }
    else
    {
        return false;
    }
}
Pixel Pixel::operator - (const Pixel &rhs) {
    unsigned char redChange;
    unsigned char greenChange;
    unsigned char blueChange;
    if((int)this->_red > (int)rhs._red){
        redChange = (int)this->_red - (int)rhs._red;
    }
    else{
        redChange = 0;
    }
    if((int)this->_green > (int)rhs._green){
        greenChange = (int)this->_green - (int)rhs._green;
    }
    else{
        greenChange = 0;
    }
    if((int)this->_blue > (int)rhs._blue){
        blueChange = (int)this->_blue - (int)rhs._blue;
    }
    else{
        blueChange = 0;
    }

    return Pixel(redChange, greenChange, blueChange);
}
Pixel Pixel::operator*(const Pixel &rhs){
    return Pixel((this->_floatRed * rhs._floatRed) * 255 + 0.5f,
                 (this->_floatGreen * rhs._floatGreen) * 255 + 0.5f,
                 (this->_floatBlue * rhs._floatBlue) * 255 + 0.5f);
}
Pixel Pixel::operator/(const Pixel &rhs) {
    float newRed = (1 - (1 - this->_floatRed) * (1 - rhs._floatRed)) * 255 + 0.5f;
    float newGreen = (1 - (1 - this->_floatGreen) * (1 - rhs._floatGreen)) * 255 + 0.5f;
    float newBlue = (1 - (1 - this->_floatBlue) * (1 - rhs._floatBlue)) * 255 + 0.5f;
    return Pixel((unsigned char)newRed, (unsigned char)newGreen, (unsigned char)newBlue);
}



