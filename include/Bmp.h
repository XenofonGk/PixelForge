#ifndef FORGE_BMP_H
#define FORGE_BMP_H
// Day 6 and Day 7: file streams and binary access.
// Notes: E-STL/file-stream-objects
//
// 24-bit BMP layout, all numbers little-endian:
//   byte 0   'B' 'M'
//   byte 2   file size (4 bytes)
//   byte 10  offset of the pixel data (4 bytes), which is 54 here
//   byte 14  header size, 40 (4 bytes)
//   byte 18  width (4 bytes)
//   byte 22  height (4 bytes)
//   byte 26  colour planes, 1 (2 bytes)
//   byte 28  bits per pixel, 24 (2 bytes)
//   byte 34  pixel data size (4 bytes)
// Pixel rows run bottom to top. Each pixel is blue, green, red.
// Each row is padded with zero bytes to a multiple of 4 bytes.
// loadBmp also accepts 32-bit files, which macOS tools can produce.
#include "Image.h"
#include <iosfwd>
#include <string>
#include <cstdint>

int bmpRowBytes(int width);                                     // Day 6
void writeLE(std::ostream& out, std::uint32_t value, int bytes); // Day 6
void saveBmp(const Image& img, const std::string& path);        // Day 6
std::uint32_t readLE(std::istream& in, int bytes);              // Day 7
Image loadBmp(const std::string& path);                         // Day 7

#endif
