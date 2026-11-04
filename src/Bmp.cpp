#include "Bmp.h"
#include "Common.h"
#include <fstream>
#include <stdexcept>
#include <vector>

int bmpRowBytes(int width) {
    // TODO Day 6: 3 bytes per pixel, rounded up to a multiple of 4. Use + 3 and a bit mask.
    NOT_IMPLEMENTED();
}
void writeLE(std::ostream& out, std::uint32_t value, int bytes) {
    // TODO Day 6: write the lowest byte first with out.put(), shifting value right by 8 each time.
    NOT_IMPLEMENTED();
}
void saveBmp(const Image& img, const std::string& path) {
    // TODO Day 6: open with ios::binary, throw std::runtime_error if it fails, write the header from Bmp.h, then the rows bottom to top.
    NOT_IMPLEMENTED();
}
std::uint32_t readLE(std::istream& in, int bytes) {
    // TODO Day 7: read one byte at a time with in.get() and rebuild the value. Throw std::runtime_error if the stream fails.
    NOT_IMPLEMENTED();
}
Image loadBmp(const std::string& path) {
    // TODO Day 7: check the 'B' 'M' signature, use seekg to read the header fields, accept 24 or 32 bits per pixel (reject others), then read rows into an Image. A 32-bit pixel has one extra byte after red.
    NOT_IMPLEMENTED();
}
