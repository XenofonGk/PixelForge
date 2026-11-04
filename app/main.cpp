// PixelForge command-line app. You do not need to change this file.
// Usage: forge script.forge
// As you finish each day, more script commands start working.
#include "Ascii.h"
#include "Bmp.h"
#include "Common.h"
#include "Filters.h"
#include "History.h"
#include "Parallel.h"
#include "Plasma.h"
#include "Queue.h"
#include "Script.h"
#include <iostream>
#include <memory>
#include <string>
#include <utility>

static std::string text(const Command& c, std::size_t i) { return std::get<std::string>(c.args.at(i)); }
static int integer(const Command& c, std::size_t i) { return static_cast<int>(asNumber(c.args.at(i))); }

class Engine {
    std::unique_ptr<History> history;
    Recent recent{5};

    const Image& image() const {
        if (!history) throw std::runtime_error("no image yet: use plasma or load first");
        return *history->current();
    }
    void open(Image img) { history = std::make_unique<History>(std::move(img)); }
public:
    void run(const Command& c) {
        recent.add(c.name);
        if (c.name == "plasma") open(plasma(integer(c, 0), integer(c, 1)));
        else if (c.name == "load") open(loadBmp(text(c, 0)));
        else if (c.name == "save") saveBmp(image(), text(c, 0));
        else if (c.name == "undo") { image(); history->undo(); }
        else if (c.name == "redo") { image(); history->redo(); }
        else if (c.name == "ascii") std::cout << toAscii(image(), integer(c, 0));
        else if (c.name == "stats") {
            double mean = meanLuma(parallelHistogram(image(), 4));
            std::cout << image().width() << " x " << image().height()
                      << ", mean brightness " << mean << " (" << levelName(static_cast<int>(mean)) << ")\n";
        }
        else if (c.name == "history") {
            for (std::size_t i = 0; i < recent.size(); ++i) std::cout << recent.at(i) << '\n';
        }
        else {
            Image next = image();
            if (c.name == "invert" || c.name == "grayscale") makeFilter(c.name)->apply(next);
            else if (c.name == "threshold") threshold(next, integer(c, 0));
            else if (c.name == "brightness") parallelApply(next, brightness(integer(c, 0)), 4);
            else if (c.name == "tint") applyFn(next, tint(asNumber(c.args.at(0)), asNumber(c.args.at(1)), asNumber(c.args.at(2))));
            else if (c.name == "equalize") equalize(next);
            else if (c.name == "blur") next = blur(next);
            else if (c.name == "sharpen") next = sharpen(next);
            else if (c.name == "median") next = medianFilter(next);
            else throw std::invalid_argument("unknown command: " + c.name);
            history->commit(std::move(next));
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: forge script.forge\n";
        return 1;
    }
    try {
        Engine engine;
        for (const Command& c : loadScript(argv[1])) {
            std::cout << "> " << c.name << '\n';
            engine.run(c);
        }
    } catch (const NotImplemented&) {
        std::cerr << "This command needs a day you have not finished yet.\n";
        return 2;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}
