#ifndef FORGE_FILTERS_H
#define FORGE_FILTERS_H
// Days 8 to 14: algorithms and the functional library.
// Notes: E-STL/algorithms, H-Deeper-Detail/arrays-and-pointers
#include "Image.h"
#include <array>
#include <cstdint>
#include <functional>
#include <vector>

int luma(Pixel p);                  // provided: brightness 0..255

// ---- Day 8: std::transform, lambdas, all_of ----
void invert(Image& img);
void grayscale(Image& img);
void threshold(Image& img, int level);   // luma >= level becomes white, otherwise black
bool isGrayscale(const Image& img);

// ---- Day 9: std::function, std::bind, ref ----
using PixelFn = std::function<Pixel(Pixel)>;
Pixel adjustBrightness(Pixel p, int amount);      // add amount to R, G, B and clamp
PixelFn brightness(int amount);                   // must use std::bind
PixelFn tint(double r, double g, double b);       // must return a lambda
void applyFn(Image& img, const PixelFn& fn);
void applyAll(Image& img, const std::vector<PixelFn>& steps);
void countInto(int& counter, Pixel p, int level); // adds 1 when luma(p) >= level
int  countWithRef(const Image& img, int level);   // must use std::bind and std::ref

// ---- Day 10: for_each, count_if, accumulate, copy_if ----
using Histogram = std::array<int, 256>;
Histogram histogram(const Image& img);
int countBright(const Image& img, int level);
double meanLuma(const Histogram& hist);
std::vector<Pixel> selectBright(const Image& img, int level);

// ---- Day 12: partial_sum ----
std::array<int, 256> cumulative(const Histogram& hist);
void equalize(Image& img);

// ---- Day 13: inner_product, pointer to an array ----
int weightedSum(const int* weights, const int* samples, int n);
Image convolve(const Image& src, const int (*kernel)[3], int divisor);
Image blur(const Image& src);
Image sharpen(const Image& src);

// ---- Day 14: sort with a comparator ----
int medianOf(std::array<int, 9> values);
Image medianFilter(const Image& src);
std::vector<int> topLumas(const Image& img, int n);  // n highest lumas, largest first

#endif
