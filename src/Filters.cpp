#include "Filters.h"
#include "Common.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

int luma(Pixel p) { return (red(p) * 299 + green(p) * 587 + blue(p) * 114) / 1000; }

void invert(Image& img) {
    std::transform(img.begin(), img.end(), img.begin(), invertRGB);
}
void grayscale(Image& img) {
    std::transform(img.begin(), img.end(), img.begin(),[](Pixel p){
        int l = luma(p);
       return pack( l,l,l,alpha(p)); } );
}
void threshold(Image& img, int level) {

    std::transform(img.begin(),img.end(), img.begin(), [level] (Pixel p) {
        int l = luma(p);
    if (l < level){
        return pack(0,0,0, alpha(p));
    } 
        return pack(255,255,255,alpha(p));
    });
}
bool isGrayscale(const Image& img) {
    // TODO Day 8: use std::all_of.
    return std::all_of(img.begin(), img.end(), [] (Pixel p) {return red(p) == green(p) && green(p) == blue(p); });

}

// ---- Day 9 ----
Pixel adjustBrightness(Pixel p, int amount) {
    return pack(clampByte(red(p) + amount), clampByte(green(p) + amount), clampByte(blue(p) + amount), alpha(p));
}
PixelFn brightness(int amount) {
   return std::bind(adjustBrightness, std::placeholders::_1, amount);
}
PixelFn tint(double r, double g, double b) {
    return [r, g, b] (Pixel p) {
    return pack(clampByte(red(p) * r),
    clampByte(green(p) * g),
    clampByte(blue(p) * b),
    alpha(p));
    };
}
void applyFn(Image& img, const PixelFn& fn) {
    std::transform(img.begin(), img.end(), img.begin(),fn);
}
void applyAll(Image& img, const std::vector<PixelFn>& steps) {
    for (const PixelFn& fn : steps){
    std::transform(img.begin(), img.end(), img.begin(),fn);
    }
}
void countInto(int& counter, Pixel p, int level) {
    if (luma(p) >= level) 
    counter++;
}
int countWithRef(const Image& img, int level) {
    int counter = 0;
    std::for_each(img.begin(), img.end(),  std::bind(countInto, std::ref(counter), std::placeholders::_1, level));
    return counter;
}

// ---- Day 10 ----
Histogram histogram(const Image& img) {
    // TODO Day 10: start with all zeros, then use std::for_each to count each pixel's luma.
    NOT_IMPLEMENTED();
}
int countBright(const Image& img, int level) {
    // TODO Day 10: use std::count_if.
    NOT_IMPLEMENTED();
}
double meanLuma(const Histogram& hist) {
    // TODO Day 10: use std::accumulate for the pixel count, and a binary lambda or inner_product for the weighted total. Return 0 for an empty histogram.
    NOT_IMPLEMENTED();
}
std::vector<Pixel> selectBright(const Image& img, int level) {
    // TODO Day 10: use std::copy_if with std::back_inserter.
    NOT_IMPLEMENTED();
}

// ---- Day 12 ----
std::array<int, 256> cumulative(const Histogram& hist) {
    // TODO Day 12: use std::partial_sum.
    NOT_IMPLEMENTED();
}
void equalize(Image& img) {
    // TODO Day 12: build the cumulative histogram, find its first non-zero value (cdfMin), then map each channel v to (cdf[v] - cdfMin) * 255 / (pixels - cdfMin). Do nothing if the bottom part would be 0.
    NOT_IMPLEMENTED();
}

// ---- Day 13 ----
int weightedSum(const int* weights, const int* samples, int n) {
    // TODO Day 13: use std::inner_product on the two raw pointer ranges.
    NOT_IMPLEMENTED();
}
Image convolve(const Image& src, const int (*kernel)[3], int divisor) {
    // TODO Day 13: for each pixel and channel, collect the 3 by 3 neighbours (clamp coordinates at the edges), sum weightedSum for each kernel row, divide, and clampByte. Keep alpha.
    NOT_IMPLEMENTED();
}
Image blur(const Image& src) {
    // TODO Day 13: call convolve with the kernel {1,2,1},{2,4,2},{1,2,1} and divisor 16.
    NOT_IMPLEMENTED();
}
Image sharpen(const Image& src) {
    // TODO Day 13: call convolve with the kernel {0,-1,0},{-1,5,-1},{0,-1,0} and divisor 1.
    NOT_IMPLEMENTED();
}

// ---- Day 14 ----
int medianOf(std::array<int, 9> values) {
    // TODO Day 14: sort the array and return the middle value.
    NOT_IMPLEMENTED();
}
Image medianFilter(const Image& src) {
    // TODO Day 14: for each channel, gather the 3 by 3 window (clamp at the edges) and use medianOf. Keep alpha.
    NOT_IMPLEMENTED();
}
std::vector<int> topLumas(const Image& img, int n) {
    // TODO Day 14: collect the lumas, sort with std::greater<int>(), and keep the first n.
    NOT_IMPLEMENTED();
}
