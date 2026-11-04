#include "Image.h"
#include "Common.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

Image::Image(int width, int height, Pixel fill) {
    if (width < 0 || height < 0){
        throw std::invalid_argument("Broken image");
    }
    w = width;
    h = height;
    data = new Pixel[width * height];
    std::fill(data,data + width * height,fill);
}
Image::~Image() {
   delete[] data;
}
Pixel& Image::at(int x, int y) {
     if (w <= x || h <= y || x < 0 || y < 0){
        throw std::out_of_range("Out of range");
    }
    return row(y)[x];
}
const Pixel& Image::at(int x, int y) const {
    if (w <= x || h <= y || x < 0 || y < 0){
        throw std::out_of_range("Out of range");
    }
    return row(y)[x];
}
Pixel* Image::row(int y) {
    return data + y * w;
}
const Pixel* Image::row(int y) const {
    return data + y * w;
}
//Copy constructor
Image::Image(const Image& other) {
    w = other.w;
    h = other.h;
    data = new Pixel[other.w * other.h];
    std::copy(other.data, other.data + other.w * other.h, data);
}
//MOVE
Image::Image(Image&& other) noexcept {
    w = other.w;
    h = other.h;
    data = other.data;
    other.data = nullptr;
    other.w = 0;
    other.h = 0;

}
Image& Image::operator=(const Image& other) {
    if (this != &other){
        delete[] data;
        w = other.w;
    h = other.h;
    data = new Pixel[other.w * other.h];
     std::copy(other.data, other.data + other.w * other.h, data);
    }
    return *this;
}
Image& Image::operator=(Image&& other) noexcept {
    if (this != &other){
        delete[] data;
        w = other.w;
        h = other.h;
        data = other.data;
        other.data = nullptr;
        other.w = 0;
        other.h = 0;
    }
    return *this;
}
bool sameImage(const Image& a, const Image& b) {
    return a.width() == b.width() && a.height() == b.height() &&
           std::equal(a.begin(), a.end(), b.begin());
}
