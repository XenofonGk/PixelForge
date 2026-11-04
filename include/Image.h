#ifndef FORGE_IMAGE_H
#define FORGE_IMAGE_H
// Day 3: raw pointers.  Day 5: rule of five.
// Notes: F-MemoryModel/raw-pointers, H-Deeper-Detail/arrays-and-pointers, E-STL/algorithms
#include "Pixel.h"

class Image {
    int w{0};
    int h{0};
    Pixel* data{nullptr};   // w * h pixels, stored in row-major order
public:
    Image() = default;
    Image(int width, int height, Pixel fill = Pixel{});
    Image(const Image& other);
    Image(Image&& other) noexcept;
    Image& operator=(const Image& other);
    Image& operator=(Image&& other) noexcept;
    ~Image();

    int width() const { return w; }
    int height() const { return h; }
    int size() const { return w * h; }
    bool empty() const { return data == nullptr; }

    Pixel& at(int x, int y);               // bounds-checked; throw std::out_of_range
    const Pixel& at(int x, int y) const;
    Pixel* row(int y);                     // pointer to the first pixel of row y
    const Pixel* row(int y) const;
    Pixel* begin() { return data; }        // STL algorithms work with raw pointers
    Pixel* end() { return data + size(); }
    const Pixel* begin() const { return data; }
    const Pixel* end() const { return data + size(); }
};

bool sameImage(const Image& a, const Image& b);

#endif
