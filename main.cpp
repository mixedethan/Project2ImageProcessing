#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "Image.h"
#include <cstring>
using namespace std;

//Functions that take in a char*/uchar/short from a fstream and returns them as a var
char readCharInfo(fstream &inFile){
    char currChar;
    inFile.read((char*)&currChar,sizeof(currChar));
    return currChar;
}
unsigned char readUCharInfo(fstream &inFile){
    char currChar;
    inFile.read((char*)&currChar,sizeof(currChar));
    return currChar;
}
short readShortInfo(fstream &inFile){
    short currShort;
    inFile.read((char*)&currShort,sizeof(currShort));
    return currShort;
}
//Function that takes in the file and stores it as an image object
Image readImageFile(const string &nameFile) {
    Image image;
    image._name = nameFile; // example -> ./input/layer1.tga
    // changes to file

    fstream inFile(nameFile, ios_base::in | ios_base::binary);

    if (!inFile.is_open()){
        cout << "Invalid argument, file does not exist." << endl;
        exit(0);
    }
    else if(inFile.is_open()){
        //Assign data from inFile Stream to the image's header object class members
        image._header._idLength = readCharInfo(inFile);
        image._header._colorMapType = readCharInfo(inFile);
        image._header._imageType = readCharInfo(inFile);
        image._header._colorMapOrigin = readShortInfo(inFile);
        image._header._colorMapLength = readShortInfo(inFile);
        image._header._colorMapDepth = readCharInfo(inFile);
        image._header._xOrigin = readShortInfo(inFile);
        image._header._yOrigin = readShortInfo(inFile);
        image._header._width = readShortInfo(inFile);
        image._header._height = readShortInfo(inFile);
        image._header._pixelDepth = readCharInfo(inFile);
        image._header._imageDescriptor = readCharInfo(inFile);

        //Assign data from inFile Stream to the image's pixel object class members
        for (unsigned int i = 0; i < (image._header._width) * (image._header._height) ; i++) {
            Pixel newPixel;
            newPixel._blue = readUCharInfo(inFile);
            newPixel._green = readUCharInfo(inFile);
            newPixel._red = readUCharInfo(inFile);
            //Convert pixels to normalized floats (0-1)
            newPixel._floatBlue = (float)newPixel._blue / 255;
            newPixel._floatGreen = (float)newPixel._green / 255;
            newPixel._floatRed = (float)newPixel._red / 255;
            image._pixelData.push_back(newPixel);
        }
    }
    else{
        cout << "Unknown Error! Please refer to Ethan!" << endl;
    }
    inFile.close();
    return image; //Returns image in a stored Image obj
}
//Function to write images
void writeFile(const Image &image, const string &fileName) {
    //Sets header information
    ofstream outFile(fileName, ios_base::out | ios_base::binary);
    if(outFile.is_open()){
    outFile.write((char*)&image._header._idLength, 1);
    outFile.write((char*)&image._header._colorMapType, 1);
    outFile.write((char*)&image._header._imageType, 1);
    outFile.write((char*)&image._header._colorMapOrigin, 2);
    outFile.write((char*)&image._header._colorMapLength, 2);
    outFile.write((char*)&image._header._colorMapDepth, 1);
    outFile.write((char*)&image._header._xOrigin, 2);
    outFile.write((char*)&image._header._yOrigin, 2);
    outFile.write((char*)&image._header._width, 2);
    outFile.write((char*)&image._header._height, 2);
    outFile.write((char*)&image._header._pixelDepth, 1);
    outFile.write((char*)&image._header._imageDescriptor, 1);
    //Seeds pixel information
    for (unsigned int i = 0; i < image._pixelData.size(); i++) {
        outFile.write((char*)&image._pixelData[i]._blue, 1);
        outFile.write((char*)&image._pixelData[i]._green, 1);
        outFile.write((char*)&image._pixelData[i]._red, 1);
        }
    outFile.close();
    }
    else{
        cout << "Failed to open out file!" << endl;
    }
}
//Function to compare images
int compareImages(const Image &image1, const Image &image2) {
    string name = image2._name;
    name.erase(0, 3);
    cout << "Testing " << image1._name << " against " << name << "..." << endl;
    int result;
    if (image1 == image2) {
        cout << "Images match. Test passed." << endl;
        result = 1;
    } else {
        cout << "Images do not match. Test failed." << endl;
        result = 0;
    }
    return result;
}
//Function to merge images
Image mergeLayers(Image &red, Image &green, Image &blue) {
    Image endImage;
    endImage._header = red._header;
    for (unsigned int i = 0; i < red._pixelData.size(); i++) {
        Pixel pixel;
        pixel._red = red._pixelData[i]._red;
        pixel._green = green._pixelData[i]._green;
        pixel._blue = blue._pixelData[i]._blue;
        endImage._pixelData.push_back(pixel);
    }
    return endImage;
}
//Function to check where a file has a .tga extension images
bool checkTGA(const string& input){
    string tga = ".tga";
    if(input.substr(input.size() - 4) == tga){
        return true;
    }
    else{
        return false;
    }
}




int main(int argc, const char* argv[]) {

    Image out;
    vector<string> args;

    for(int i = 1; i < argc; i++){ //build a vector of the args
        args.push_back(argv[i]);
    }


    //Help feature
    if (argc == 1 || args[0] == "--help") { //If no arguments are given or --help, print usage
        cout << "Project 2: Image Processing, Spring 2023" << endl;
        cout << "\nUsage:" << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
        //THROW out of range exception for string when argv[1] is < 4
    }
    else if (args[0].size() < 5) {
        cout << "Invalid file name." << endl;
        return 0;
    }
        //If argv[1] doesn't end with .tga, print "Inavlid file name."
    else if (!checkTGA(args[0])) {
        cout << "Invalid file name." << endl;
        return 0;
    }
    else if (args[1].size() < 5) {
        cout << "Invalid file name." << endl;
        return 0;
    }
    else if(argc < 3){
        cout << "Missing argument." << endl;
        return 0;
}
    if (args[1].size() < 5) {
        cout << "Invalid file name." << endl;
        return 0;
    }
        //If argv[2] doesn't end with .tga, print "Inavlid file name."
    else if (!checkTGA(args[1])) {
        cout << "Invalid file name." << endl;
        return 0;
    }

    fstream inFS;
    inFS.open(args[1]);
    if(!inFS.is_open()){
        cout << "File does not exist." << endl;
        return 0;
    }

    //Read in the first/tracking img
    Image trackingImage = readImageFile(args[1]);
    trackingImage._name = args[1];

    for(int k = 3; k < argc; k++){
        //argv[3] is the first method

        if(strcmp(argv[k], "multiply") == 0){ //If argv[3] is multiply
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }
            if(!checkTGA(argv[k + 1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            Image second = readImageFile(argv[k + 1]);
            second._name = argv[k + 1];
            Image temp = trackingImage * second;
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "subtract") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }
                if(!checkTGA(argv[k + 1])) {
                    cout << "Invalid argument, invalid file name." << endl;
                    return 0;
                }
                Image second = readImageFile(argv[k + 1]);
                second._name = argv[k + 1];
                Image temp = trackingImage - second;
                trackingImage = temp;
                k++;
        }
        else if(strcmp(argv[k], "overlay") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }
            if(!checkTGA(argv[k + 1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            Image second = readImageFile(argv[k + 1]);
            second._name = argv[k + 1];
            Image temp = trackingImage | second;
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "screen") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }
            if(!checkTGA(argv[k + 1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            Image second = readImageFile(argv[k + 1]);
            second._name = argv[k + 1];
            Image temp = second / trackingImage;
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "combine") == 0){
            if(k + 2 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }
            if(!checkTGA(argv[k + 1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            if(!checkTGA(argv[k + 2])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            Image second = readImageFile(argv[k + 1]);
            Image third = readImageFile(argv[k + 2]);
            second._name = argv[k + 1];
            third._name = argv[k + 2];
            Image temp = mergeLayers(trackingImage,second,third);
            trackingImage = temp;
            k += 2;
        }
        else if(strcmp(argv[k], "flip") == 0){
            Image temp = trackingImage.rotate180();
            trackingImage = temp;
        }
        else if(strcmp(argv[k], "onlyred") == 0){
            Image temp = trackingImage.separateRed();
            trackingImage = temp;
        }
        else if(strcmp(argv[k], "onlyblue") == 0){
            Image temp = trackingImage.separateBlue();
            trackingImage = temp;
        }
        else if(strcmp(argv[k], "onlygreen") == 0){
            Image temp = trackingImage.separateGreen();
            trackingImage = temp;
        }
        else if(strcmp(argv[k], "addred") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }
            int numIncrease;
            try {
                numIncrease = stoi(argv[k + 1]);
            }
            catch (const invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            Image temp = trackingImage.addRed(numIncrease);
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "addgreen") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }
            int numIncrease;
            try {
                numIncrease = stoi(argv[k + 1]);
            }
            catch (const invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            Image temp = trackingImage.addGreen(numIncrease);
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "addblue") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }

            int numIncrease;
            try {
                numIncrease = stoi(argv[k + 1]);
            }
            catch (const invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            Image temp = trackingImage.addBlue(numIncrease);
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "scalered") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }

            int numIncrease;
            try {
                numIncrease = stoi(argv[k + 1]);
            }
            catch (const invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            Image temp = trackingImage.multiplyRed(numIncrease);
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "scalegreen") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }

            int numIncrease;
            try {
                numIncrease = stoi(argv[k + 1]);
            }
            catch (const invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            Image temp = trackingImage.multiplyGreen(numIncrease);
            trackingImage = temp;
            k++;
        }
        else if(strcmp(argv[k], "scaleblue") == 0){
            if(k + 1 >= argc){ //
                cout << "Missing argument." << endl;
                exit(0);
            }

            int numIncrease;
            try {
                numIncrease = stoi(argv[k + 1]);
            }
            catch (const invalid_argument) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }

            Image temp = trackingImage.multiplyBlue(numIncrease);
            trackingImage = temp;
            k++;
        }
        else{
            cout << "Invalid method name." << endl;
            return 0;
        }

    }

    writeFile(trackingImage, argv[1]); //Writes final image

    return 0;

}

