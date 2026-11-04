#ifndef FORGE_PIXEL_H
#define FORGE_PIXEL_H
// Day 1: bit-wise expressions.  Day 2: pre-processor directives.
// Notes: H-Deeper-Detail/bit-wise-expressions, H-Deeper-Detail/pre-processor-directives
#include <cstddef>
#include <cstdint>

// A pixel stores 0xRRGGBBAA: red in the high byte, alpha in the low byte.
struct Pixel {
    std::uint32_t value{0};

    // These counters let the tests catch memory leaks in Image.
    // Keep using plain new Pixel[n] and delete[]; they call these for you.
    static int liveArrays;
    static void* operator new[](std::size_t bytes);
    static void operator delete[](void* p) noexcept;
};

inline bool operator==(Pixel a, Pixel b) { return a.value == b.value; }
inline bool operator!=(Pixel a, Pixel b) { return a.value != b.value; }

// ---- Day 1 ----
Pixel pack(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);
std::uint8_t red(Pixel p);
std::uint8_t green(Pixel p);
std::uint8_t blue(Pixel p);
std::uint8_t alpha(Pixel p);
Pixel invertRGB(Pixel p);                       // flip R, G, B; keep alpha
Pixel flipChannelBits(Pixel p, std::uint32_t mask); // exclusive-or with a mask
bool  isOddRed(Pixel p);                        // test the lowest bit of red
int   remainderPow2(int value, int powerOfTwo); // value % powerOfTwo using & only

#define FORGE_SQUARE(X) ((X) * (X) )
#define FORGE_MAX(A, B) ((A) > (B) ? (A) : (B))
#define FORGE_CLAMP(X, LO, HI) ((X) < (LO) ? (LO) : (X) > (HI) ? (HI) : (X))

// A macro evaluates its argument more than once. This function does not.
int clampByte(int value);                    // clamp to 0..255, argument used once
int countEvaluations();                      // how many times FORGE_SQUARE(next()) calls next()

// True only when FORGE_DEBUG is defined before this header is included.
#if defined(FORGE_DEBUG)
#define FORGE_LOG(MSG) forgeLog(__FILE__, __LINE__, MSG)
#else
#define FORGE_LOG(MSG)
#endif
void forgeLog(const char* file, int line, const char* msg);

#endif
