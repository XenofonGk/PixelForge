#include "Plasma.h"
#include <cmath>

Image plasma(int w, int h) {
    Image img(w, h);
    for (int y = 0; y < h; ++y) {
        Pixel* row = img.row(y);
        for (int x = 0; x < w; ++x) {
            double v = std::sin(x * 0.03) + std::sin(y * 0.05) + std::sin((x + y) * 0.02);
            int r = static_cast<int>(127 + 127 * std::sin(v * 2.0));
            int g = static_cast<int>(127 + 127 * std::sin(v * 2.0 + 2.1));
            int b = static_cast<int>(127 + 127 * std::sin(v * 2.0 + 4.2));
            row[x] = pack(static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g),
                          static_cast<std::uint8_t>(b));
        }
    }
    return img;
}

