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
    std::uint32_t result = 0;
    for (int i = 0; i < bytes; i++){
        std::uint32_t b = in.get();
        if (!in){
            throw std::runtime_error("Cannot read byte");
        }
        result = result | (b << (i * 8));
    }
    return result;
}
Image loadBmp(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in){
        throw std::runtime_error("Cannot open file");
    }
    if (in.get() != 'B' || in.get() != 'M'){ 
        throw std::runtime_error("Not a BMP file");
    }
        in.seekg(18);
        int width = readLE(in,4);
        int height = readLE(in,4);
        in.seekg(28);
        int bpp = readLE(in,2);
        if (bpp != 24 && bpp != 32){
           throw std::runtime_error("Unsupported bits per pixel"); 
        }
        in.seekg(10);
        int offset = readLE(in,4);
        Image img(width, height);
        in.seekg(offset);
        for (int y = img.height()- 1; y >= 0; y--){
        for (int x = 0; x< img.width(); x++){
        int b = in.get();
        int g = in.get();
        int r = in.get();
         if (bpp == 32){
            in.get();
         }
         img.at(x,y) = pack(r,g,b);
         
        }
        if (bpp == 24){
        int pad = bmpRowBytes(img.width()) - img.width() * 3;
        for ( int i = 0; i < pad; i++){
            in.get();
        }
    }
    }  
    return img;
}

