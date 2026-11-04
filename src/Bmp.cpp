#include "Bmp.h"
#include "Common.h"
#include <fstream>
#include <stdexcept>
#include <vector>

int bmpRowBytes(int width) {
   return ((width * 3) + 3) & (~3);
}
void writeLE(std::ostream& out, std::uint32_t value, int bytes) {
    for (int i = 0; i < bytes; i ++){
    out.put(value & 0xFF);
    value = value >> 8;
    }
}
void saveBmp(const Image& img, const std::string& path) {
    // TODO Day 6: open with ios::binary, throw std::runtime_error if it fails, write the header from Bmp.h, then the rows bottom to top.
    
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot open file");
    }
    out.put('B');
    out.put('M');
    int dataSize = bmpRowBytes(img.width() )* img.height();
    writeLE(out, 54 + dataSize, 4);
    writeLE(out, 0 ,4);
    writeLE(out, 54, 4);
    writeLE(out, 40, 4);
    writeLE(out, img.width(), 4);
    writeLE(out,img.height(),4);
    writeLE(out,1, 2);
    writeLE(out,24,2);
    writeLE(out, 0 ,4);
    writeLE(out,dataSize,4);
    writeLE(out,0,4);
    writeLE(out,0,4);
    writeLE(out,0,4);
    writeLE(out,0,4);
    for (int y = img.height()- 1; y >= 0; y--){
        for (int x = 0; x< img.width(); x++){
            Pixel p = img.at(x,y);
            out.put(blue(p));
            out.put(green(p));
            out.put(red(p));
        }
        int pad = bmpRowBytes(img.width()) - img.width() * 3;
        for ( int i = 0; i < pad; i++){
            out.put(0);
        }
    }
}
std::uint32_t readLE(std::istream& in, int bytes) {
    // TODO Day 7: read one byte at a time with in.get() and rebuild the value. Throw std::runtime_error if the stream fails.
    NOT_IMPLEMENTED();
}
Image loadBmp(const std::string& path) {
    // TODO Day 7: check the 'B' 'M' signature, use seekg to read the header fields, accept 24 or 32 bits per pixel (reject others), then read rows into an Image. A 32-bit pixel has one extra byte after red.
    NOT_IMPLEMENTED();
}
