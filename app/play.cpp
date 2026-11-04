// Your playground. Edit this file freely to try each day's work on a real picture.
// Build:  g++ -std=c++17 -Wall -pthread -Iinclude src/*.cpp app/play.cpp -o play
// Run:    ./play       then open output/play.bmp
// Saving needs Day 6. Before that, this program stops with a TODO message.
#include "Bmp.h"
#include "Common.h"
#include "Filters.h"
#include "Plasma.h"
#include <iostream>

int main() {
    try {
        Image img = plasma(640, 400);
        // Image img = loadBmp("my_photo.bmp");        // after Day 7

        // Remove the // from a line once you have finished its day:
        // invert(img);                                // Day 8
        // grayscale(img);                             // Day 8
        // applyFn(img, brightness(40));               // Day 9
        // applyFn(img, tint(1.2, 0.9, 0.6));          // Day 9
        // equalize(img);                              // Day 12
        // img = blur(img);                            // Day 13
        // img = sharpen(img);                         // Day 13
        // img = medianFilter(img);                    // Day 14

        saveBmp(img, "output/play.bmp");
        std::cout << "Saved output/play.bmp\n";
    } catch (const NotImplemented&) {
        std::cout << "This needs a day you have not finished yet.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}
