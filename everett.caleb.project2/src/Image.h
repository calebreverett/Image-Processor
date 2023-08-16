
#ifndef UNTITLED3_IMAGE_H
#define UNTITLED3_IMAGE_H
#include <fstream>
#include <vector>
using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

class Image {
    Header header;
    vector<Pixel> pixels;
public:
    Image();
    Image(const string &fileName);
    void PrintFile(const string &fileName);
    void Multiply(Image foreground);
    void Subtract(Image foreground);
    void Screen(Image foreground);
    void Overlay(Image foreground);
    void Add(int blue, int green, int red);
    void Scale(int blue, int green, int red);
    void Separate(string color);
    void Combine(Image blue, Image green, Image red);
    void Flip();
    void Expand(short scale);
    void Include(Image bottomLeft, Image bottomRight, Image topLeft, Image topRight);
    bool operator==(const Image &rhs);
};


#endif //UNTITLED3_IMAGE_H
