#include "Image.h"
#include <vector>
using namespace std;

Image::Image(string name, Header &header, vector<Pixel> &_pixelData){
    _name = name;
    _header = header;
    _pixelData = _pixelData;
}

//Overloaded Operators
Image& Image::operator=(Image &rhs){
   this->_header = rhs._header;
    this->_pixelData = rhs._pixelData;
    return *this;
}
bool Image::operator==(const Image &rhs) const {
    for (unsigned int i = 0; i < _pixelData.size(); i++) {
        if (_pixelData[i] == rhs._pixelData[i])
        {
            return true;
        }
    }
    return false;
}
Image Image::operator*(const Image &rhs){
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        endImage._pixelData[i] = endImage._pixelData[i] * rhs._pixelData[i];
    }
    return endImage;
}
Image Image::operator/(const Image &rhs) {
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        endImage._pixelData[i] = endImage._pixelData[i] / rhs._pixelData[i];
    }
    return endImage;
}
Image Image::operator-(const Image &rhs){
    Image image;
    image._header = _header;
    for (unsigned int i = 0; i < _pixelData.size(); i++) {
        image._pixelData.push_back(_pixelData[i] - rhs._pixelData[i]);
    }
    return image;
}
Image Image::operator|(Image &rhs) {
    Image out = *this;
    float screen;
    for (unsigned int i = 0; i < rhs._pixelData.size(); i++) {
        if (rhs._pixelData[i]._floatRed <= 0.5) {
            float temp = 2 * out._pixelData[i]._floatRed * rhs._pixelData[i]._floatRed;
            if (temp * 255 + 0.5f < 255) {
                out._pixelData[i]._red = temp * 255 + 0.5f;
            } else {
                out._pixelData[i]._red = 255;
            }
        } else {
            screen = 1 - 2 * (1 - out._pixelData[i]._floatRed) * (1 - rhs._pixelData[i]._floatRed);
            if (screen >= 0) {
                out._pixelData[i]._red = screen * 255 + 0.5f;
            } else {
                out._pixelData[i]._red = 0;
            }
        }
        if (rhs._pixelData[i]._floatBlue <= 0.5) {
            float temp = 2 * out._pixelData[i]._floatBlue * rhs._pixelData[i]._floatBlue;
            if (temp * 255 + 0.5f < 255) {
                out._pixelData[i]._blue = temp * 255 + 0.5f;
            } else {
                out._pixelData[i]._blue = 255;
            }
        } else {
            screen = 1 - 2 * (1 - out._pixelData[i]._floatBlue) * (1 - rhs._pixelData[i]._floatBlue);
            if (screen >= 0) {
                out._pixelData[i]._blue = screen * 255 + 0.5f;
            } else {
                out._pixelData[i]._blue = 0;
            }
        }
        if (rhs._pixelData[i]._floatGreen <= 0.5) {
            float temp = 2 * out._pixelData[i]._floatGreen * rhs._pixelData[i]._floatGreen;
            if (temp * 255 + 0.5f < 255) {
                out._pixelData[i]._green = temp * 255 + 0.5f;
            } else {
                out._pixelData[i]._green = 255;
            }
        } else {
            screen = 1 - 2 * (1 - out._pixelData[i]._floatGreen) * (1 - rhs._pixelData[i]._floatGreen);
            if (screen >= 0) {
                out._pixelData[i]._green = screen * 255 + 0.5f;
            } else {
                out._pixelData[i]._green = 0;
            }
        }
    }
    return out;
}


//Image Adjustments
Image Image::rotate180() {
    Image endImage = *this;
    vector<Pixel> tempVec(endImage._pixelData.size());
    //Copy image data to temporary vector in reverse order
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        tempVec[endImage._pixelData.size() - i - 1] = endImage._pixelData[i];
    }
    //Copy pixels from temporary vector back to image data
    endImage._pixelData = tempVec;

    return endImage;
}
Image Image::addBlue(const int &numIncrease) {
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        if ((int)endImage._pixelData[i]._blue + numIncrease > 255) {
            endImage._pixelData[i]._blue = 255;
        }
        else{
            endImage._pixelData[i]._blue = (int)endImage._pixelData[i]._blue + numIncrease;
        }
    }
    return endImage;
}
Image Image::addGreen(const int &numIncrease) {
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        if ((int)endImage._pixelData[i]._green + numIncrease > 255) {
            endImage._pixelData[i]._green = 255;
        }
        else{
            endImage._pixelData[i]._green = (int)endImage._pixelData[i]._green + numIncrease;
        }
    }
    return endImage;
}
Image Image::addRed(const int &numIncrease) {
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        if ((int)endImage._pixelData[i]._red + numIncrease > 255) {
            endImage._pixelData[i]._red = 255;
        }
        else{
            endImage._pixelData[i]._red = (int)endImage._pixelData[i]._red + numIncrease;
        }
    }
    return endImage;
}
Image Image::multiplyBlue(const int &times) {
    Image currImage = *this;
    for (unsigned int i = 0; i < currImage._pixelData.size(); i++) {
        float newBlue = (currImage._pixelData[i]._floatBlue * times) * 255 + 0.5f;
        if (newBlue < 255) {
            currImage._pixelData[i]._blue = newBlue;
        } else {
            currImage._pixelData[i]._blue = 255;
        }
    }
    return currImage;
}
Image Image::multiplyGreen(const int &times) {
    Image currImage = *this;
    for (unsigned int i = 0; i < currImage._pixelData.size(); i++) {
        float newGreen = (currImage._pixelData[i]._floatGreen * times) * 255 + 0.5f;
        if (newGreen < 255) {
            currImage._pixelData[i]._green = newGreen;
        } else {
            currImage._pixelData[i]._green = 255;
        }
    }
    return currImage;
}
Image Image::multiplyRed(const int &times) {
    Image currImage = *this;
    for (unsigned int i = 0; i < currImage._pixelData.size(); i++) {
        float newRed = (currImage._pixelData[i]._floatRed * times) * 255 + 0.5f;
        if (newRed < 255) {
            currImage._pixelData[i]._red = newRed;
        } else {
            currImage._pixelData[i]._red = 255;
        }
    }
    return currImage;
}
Image Image::separateBlue() {
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        endImage._pixelData[i]._red = endImage._pixelData[i]._blue;
        endImage._pixelData[i]._green = endImage._pixelData[i]._blue;
    }
    return endImage;
}
Image Image::separateGreen() {
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        endImage._pixelData[i]._red = endImage._pixelData[i]._green;
        endImage._pixelData[i]._blue = endImage._pixelData[i]._green;
    }
    return endImage;
}
Image Image::separateRed() {
    Image endImage = *this;
    for (unsigned int i = 0; i < endImage._pixelData.size(); i++) {
        endImage._pixelData[i]._green = endImage._pixelData[i]._red;
        endImage._pixelData[i]._blue = endImage._pixelData[i]._red;
    }
    return endImage;
}





