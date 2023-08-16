//
// Created by Caleb Everett on 3/20/22.
//

#include <vector>
#include "Image.h"
#include <iostream>
Image::Image() {
    header.colorMapOrigin = 0;
    header.colorMapLength = 0;
    header.xOrigin = 0;
    header.height = 0;
    header.width = 0;
    header.imageDescriptor = 0;
    header.bitsPerPixel = 0;
    header.colorMapDepth = 0;
    header.dataTypeCode = 0;
    header.colorMapType = 0;
    header.idLength = 0;
}

Image::Image(const string &fileName) {
    ifstream inFile(fileName, ios_base::binary);

    inFile.read(&header.idLength, sizeof(header.idLength));

    inFile.read(&header.colorMapType, sizeof(header.colorMapType));
    inFile.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    inFile.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    inFile.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    inFile.read(&header.colorMapDepth, sizeof(header.colorMapDepth));

    inFile.read((char*)&header.xOrigin, sizeof(header.xOrigin));
    inFile.read((char*)&header.yOrigin, sizeof(header.yOrigin));
    inFile.read((char*)&header.width, sizeof(header.width));
    inFile.read((char*)&header.height, sizeof(header.height));

    inFile.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    inFile.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    for(int i = 0; i < header.width * header.height; i++){
        Pixel tempPixel;
        inFile.read((char*)&tempPixel.blue, sizeof(tempPixel.blue));
        inFile.read((char*)&tempPixel.green, sizeof(tempPixel.green));
        inFile.read((char*)&tempPixel.red, sizeof(tempPixel.red));
        pixels.push_back(tempPixel);
    }
}

void Image::PrintFile(const string &fileName) {
    ofstream outFile(fileName, ios_base::binary);

    outFile.write(&header.idLength, sizeof(header.idLength));

    outFile.write(&header.colorMapType, sizeof(header.colorMapType));
    outFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
    outFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    outFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    outFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));

    outFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
    outFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
    outFile.write((char*)&header.width, sizeof(header.width));
    outFile.write((char*)&header.height, sizeof(header.height));

    outFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    outFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    for(int i = 0; i < pixels.size(); i++){
        Pixel tempPixel = pixels.at(i);
        outFile.write((char*)&tempPixel.blue, sizeof(tempPixel.blue));
        outFile.write((char*)&tempPixel.green, sizeof(tempPixel.green));
        outFile.write((char*)&tempPixel.red, sizeof(tempPixel.red));
    }
}

void Image::Multiply(Image foreground) {
    for(int i = 0; i < pixels.size(); i++){
        float tempBlue = (float) pixels.at(i).blue / 255.0f;
        float tempGreen = (float) pixels.at(i).green / 255.0f;
        float tempRed = (float) pixels.at(i).red / 255.0f;
        float tempBlue2 = (float) foreground.pixels.at(i).blue / 255.0f;
        float tempGreen2 = (float) foreground.pixels.at(i).green / 255.0f;
        float tempRed2 = (float) foreground.pixels.at(i).red / 255.0f;
        tempBlue = tempBlue * tempBlue2 * 255.0f + 0.5f;
        tempGreen = tempGreen * tempGreen2 * 255.0f + 0.5f;
        tempRed = tempRed * tempRed2 * 255.0f + 0.5F;
        pixels.at(i).blue = (unsigned char)tempBlue;
        pixels.at(i).green = (unsigned char)tempGreen;
        pixels.at(i).red = (unsigned char)tempRed;
    }
}

void Image::Subtract(Image foreground) {
    for(int i = 0; i < pixels.size(); i++){
        int tempBlue = (int) pixels.at(i).blue - (int)foreground.pixels.at(i).blue;
        if(tempBlue < 0){
            tempBlue = 0;
        }
        int tempGreen = (int) pixels.at(i).green - (int)foreground.pixels.at(i).green;
        if(tempGreen < 0){
            tempGreen = 0;
        }
        int tempRed = (int) pixels.at(i).red - (int)foreground.pixels.at(i).red;
        if(tempRed < 0){
            tempRed = 0;
        }
        pixels.at(i).blue = (unsigned char)tempBlue;
        pixels.at(i).green = (unsigned char)tempGreen;
        pixels.at(i).red = (unsigned char)tempRed;
    }
}

void Image::Screen(Image foreground) {
    for(int i = 0; i < pixels.size(); i++){
        float tempBlue = (float) pixels.at(i).blue / 255;
        float tempBlue2 = (float) foreground.pixels.at(i).blue / 255;
        pixels.at(i).blue = (unsigned char) (255 * (1 - (1 -tempBlue) * (1 - tempBlue2)) + 0.5f);

        float tempGreen = (float) pixels.at(i).green / 255;
        float tempGreen2 = (float) foreground.pixels.at(i).green / 255;
        pixels.at(i).green = (unsigned char) (255 * (1 - (1 -tempGreen) * (1 - tempGreen2)) + 0.5f);

        float tempRed = (float) pixels.at(i).red / 255;
        float tempRed2 = (float) foreground.pixels.at(i).red / 255;
        pixels.at(i).red = (unsigned char) (255 * (1 - (1 -tempRed) * (1 - tempRed2)) + 0.5f);
    }
}

void Image::Overlay(Image foreground) {
    for(int i = 0; i < pixels.size(); i++){
        int grey = (int) pixels.at(i).blue + pixels.at(i).green + pixels.at(i).red;
        if(grey <= 382.5){
            float tempRed = (float) pixels.at(i).red / 255.0f;
            float tempRed2 = (float) foreground.pixels.at(i).red / 255.0f;
            tempRed = 2 * tempRed * tempRed2 * 255.0f + 0.5f;
            if(tempRed > 255){
                tempRed = 255;
            }
            pixels.at(i).red = (unsigned char)tempRed;

            float tempGreen = (float) pixels.at(i).green / 255.0f;
            float tempGreen2 = (float) foreground.pixels.at(i).green / 255.0f;
            tempGreen = 2 * tempGreen * tempGreen2 * 255.0f + 0.5f;
            if(tempGreen > 255){
                tempGreen = 255;
            }
            pixels.at(i).green = (unsigned char)tempGreen;

            float tempBlue = (float) pixels.at(i).blue / 255.0f;
            float tempBlue2 = (float) foreground.pixels.at(i).blue / 255.0f;
            tempBlue = 2 * tempBlue * tempBlue2 * 255.0f + 0.5f;
            if(tempBlue > 255){
                tempBlue = 255;
            }
            pixels.at(i).blue = (unsigned char)tempBlue;
        }
        else{
            float tempRed = (float) (pixels.at(i).red) / 255.0f;
            float tempRed2 = (float) (foreground.pixels.at(i).red) / 255.0f;
            tempRed = (255 * (1 - (2 * (1 - tempRed) * (1 - tempRed2))) + 0.5f);
            if(tempRed > 255){
                tempRed = 255;
            }
            pixels.at(i).red = (unsigned char) tempRed;

            float tempGreen = (float) (pixels.at(i).green) / 255.0f;
            float tempGreen2 = (float) (foreground.pixels.at(i).green) / 255.0f;
            tempGreen = (255 * (1 - (2 * (1 - tempGreen) * (1 - tempGreen2))) + 0.5f);
            if(tempGreen > 255){
                tempGreen = 255;
            }
            pixels.at(i).green = (unsigned char) tempGreen;

            float tempBlue = (float) (pixels.at(i).blue) / 255.0f;
            float tempBlue2 = (float) (foreground.pixels.at(i).blue) / 255.0f;
            tempBlue = (255 * (1 - (2 * (1 - tempBlue) * (1 - tempBlue2))) + 0.5f);
            if(tempBlue > 255){
            tempBlue = 255;
            }
            pixels.at(i).blue = (unsigned char) tempBlue;
        }
    }
}

void Image::Add(int blue, int green, int red) {
    for(int i = 0; i < pixels.size(); i++){
        int tempBlue = (int) pixels.at(i).blue + blue;
        if(tempBlue > 255){
            tempBlue = 255;
        }
        pixels.at(i).blue = (unsigned char) tempBlue;

        int tempGreen = (int) pixels.at(i).green + green;
        if(tempGreen > 255){
            tempGreen = 255;
        }
        pixels.at(i).green = (unsigned char) tempGreen;

        int tempRed = (int) pixels.at(i).red + red;
        if(tempRed > 255){
            tempRed = 255;
        }
        pixels.at(i).red = (unsigned char) tempRed;
    }
}

void Image::Scale(int blue, int green, int red){
    for(int i = 0; i < pixels.size(); i++){
        int tempBlue = (int) pixels.at(i).blue * blue;
        if(tempBlue > 255){
            tempBlue = 255;
        }
        pixels.at(i).blue = (unsigned char) tempBlue;

        int tempGreen = (int) pixels.at(i).green * green;
        if(tempGreen > 255){
            tempGreen = 255;
        }
        pixels.at(i).green = (unsigned char) tempGreen;

        int tempRed = (int) pixels.at(i).red * red;
        if(tempRed > 255){
            tempRed = 255;
        }
        pixels.at(i).red = (unsigned char) tempRed;
    }
}

void Image::Separate(string color) {
    if(color == "blue"){
        for(int i = 0; i < pixels.size(); i++){
            pixels.at(i).green = pixels.at(i).blue;
            pixels.at(i).red = pixels.at(i).blue;
        }
    }
    else if(color == "green"){
        for(int i = 0; i < pixels.size(); i++){
            pixels.at(i).red = pixels.at(i).green;
            pixels.at(i).blue = pixels.at(i).green;
        }
    }
    else if(color == "red"){
        for(int i = 0; i < pixels.size(); i++){
            pixels.at(i).blue = pixels.at(i).red;
            pixels.at(i).green = pixels.at(i).red;
        }
    }
    else{
        cout << "Separator Failed: Use a pixel color" << endl;
    }
}

void Image::Combine(Image blue, Image green, Image red) {
    for(int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = blue.pixels.at(i).blue;
        pixels.at(i).green = green.pixels.at(i).green;
        pixels.at(i).red = red.pixels.at(i).red;
    }
}

void Image::Flip() {
    Image tempImage = *this;
    for(int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = tempImage.pixels.at(pixels.size() - (i + 1)).blue;
        pixels.at(i).green = tempImage.pixels.at(pixels.size() - (i + 1)).green;
        pixels.at(i).red = tempImage.pixels.at(pixels.size() - (i + 1)).red;
    }
}

void Image::Expand(short scale) {
    for(int i = 0; i < (scale * scale * header.width * header.height) - (header.width * header.height); i++){
        Pixel pixel;
        pixel.blue = 0;
        pixel.green = 0;
        pixel.red = 0;
        pixels.push_back(pixel);
    }
    header.width *= scale;
    header.height *= scale;
}

void Image::Include(Image bottomLeft, Image bottomRight, Image topLeft, Image topRight) {
    for (int i = 0; i < bottomLeft.header.height; i++) {
        for(int j = 0; j < bottomLeft.header.width; j++){
            pixels.at((2 * i * bottomLeft.header.width) + j) = bottomLeft.pixels.at(i * bottomLeft.header.width + j);
        }
        for(int j = 0; j < bottomRight.header.width; j++){
            pixels.at((2 * i * bottomLeft.header.width) + bottomLeft.header.width + j) = bottomRight.pixels.at(i * bottomRight.header.width + j);
        }
    }
    for (int i = 0; i < topLeft.header.height; i++) {
        for(int j = 0; j < topLeft.header.width; j++){
            pixels.at((2 * i * topLeft.header.width) + j + (2 * bottomLeft.header.width * bottomRight.header.height)) = topLeft.pixels.at(i * topLeft.header.width + j);
        }
        for(int j = 0; j < topRight.header.width; j++){
            pixels.at((2 * i * topLeft.header.width) + topLeft.header.width + j + (2 * bottomLeft.header.width * topRight.header.height)) = topRight.pixels.at(i * topRight.header.width + j);
        }
    }
}

bool Image::operator==(const Image &rhs) {
    if(header.height == rhs.header.height && header.width == rhs.header.width){
        int pixelAmt = 0;
        for(int i = 0; i < pixels.size(); i++){
            if(pixels.at(i).blue == rhs.pixels.at(i).blue && pixels.at(i).green == rhs.pixels.at(i).green
            && pixels.at(i).red == rhs.pixels.at(i).red){
                pixelAmt++;
            }
        }
        if(pixelAmt == pixels.size()){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}