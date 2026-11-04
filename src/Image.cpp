#include "Image.h"
#include "Common.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

Image::Image(int width, int height, Pixel fill) {
    // TODO Day 3: reject negative sizes with std::invalid_argument, allocate width * height pixels with new[], and fill them with std::fill.
    NOT_IMPLEMENTED();
}
Image::~Image() {
    // TODO Day 3: release the pixel array with delete[].
}
Pixel& Image::at(int x, int y) {
    // TODO Day 3: throw std::out_of_range for a bad x or y, otherwise return the pixel. Use row().
    NOT_IMPLEMENTED();
}
const Pixel& Image::at(int x, int y) const {
    // TODO Day 3: same as above, for const images.
    NOT_IMPLEMENTED();
}
Pixel* Image::row(int y) {
    // TODO Day 3: use pointer arithmetic. Rows are stored one after another.
    NOT_IMPLEMENTED();
}
const Pixel* Image::row(int y) const {
    // TODO Day 3: same as above, for const images.
    NOT_IMPLEMENTED();
}
Image::Image(const Image& other) {
    // TODO Day 5: deep copy: allocate a new array and copy every pixel with std::copy.
    NOT_IMPLEMENTED();
}
Image::Image(Image&& other) noexcept {
    // TODO Day 5: take the pointer and sizes, then leave other empty.
}
Image& Image::operator=(const Image& other) {
    // TODO Day 5: check self-assignment, release the old array, then deep copy.
    NOT_IMPLEMENTED();
}
Image& Image::operator=(Image&& other) noexcept {
    // TODO Day 5: check self-assignment, release the old array, then take over other's array. Keep the return below.
    return *this;
}
bool sameImage(const Image& a, const Image& b) {
    return a.width() == b.width() && a.height() == b.height() &&
           std::equal(a.begin(), a.end(), b.begin());
}
