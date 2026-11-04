#include "Pixel.h"
#include "Common.h"
#include <iostream>
#include <new>

int Pixel::liveArrays = 0;
void* Pixel::operator new[](std::size_t bytes) { ++liveArrays; return ::operator new[](bytes); }
void Pixel::operator delete[](void* p) noexcept { if (p) --liveArrays; ::operator delete[](p); }

Pixel pack(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
    Pixel p;
    p.value = (std::uint32_t(r) << 24) | (std::uint32_t(g) << 16) | (std::uint32_t(b) << 8) | a;
    return p;
}
std::uint8_t red(Pixel p) {
    return (p.value >> 24) & 0xFF;
}
std::uint8_t green(Pixel p) {
    return (p.value >> 16) & 0xFF;
}
std::uint8_t blue(Pixel p) {

    return (p.value >> 8) & 0xFF;
}
std::uint8_t alpha(Pixel p) {
   return p.value & 0xFF;
}
Pixel invertRGB(Pixel p) {
    Pixel q;
    q.value = (~p.value & 0xFFFFFF00u) | (p.value & 0xFF);
    return q;
}
Pixel flipChannelBits(Pixel p, std::uint32_t mask) {
   p.value ^= mask;
   return p;
    }
bool isOddRed(Pixel p) {
    return red(p) & 1;
}
int remainderPow2(int value, int powerOfTwo) {
   return value & (powerOfTwo - 1);
}

int clampByte(int value) {
    // TODO Day 2: write this as a normal function. It takes the place of a macro.
    NOT_IMPLEMENTED();
}
static int s_calls = 0;
static int next() { return ++s_calls; }
int countEvaluations() {
    s_calls = 0;
    int ignored = FORGE_SQUARE(next());
    (void)ignored;
    return s_calls;
}
void forgeLog(const char* file, int line, const char* msg) {
    std::cerr << file << ':' << line << ": " << msg << '\n';
}
