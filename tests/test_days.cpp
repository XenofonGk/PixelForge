#include "check.h"
#include "Ascii.h"
#include "Bmp.h"
#include "Common.h"
#include "FilterClasses.h"
#include "Filters.h"
#include "History.h"
#include "Parallel.h"
#include "Queue.h"
#include "Script.h"
#include "Stack.h"
#include <cstdio>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <thread>
#include <variant>

static Image sample() {
    Image img(4, 3);
    int v = 0;
    for (Pixel& p : img) {
        p = pack(static_cast<std::uint8_t>(v * 20), static_cast<std::uint8_t>(250 - v * 20),
                 static_cast<std::uint8_t>(v * 7));
        ++v;
    }
    return img;
}
static Image grayRamp(int w, int h, int low, int high) {
    Image img(w, h);
    int n = img.size(), i = 0;
    for (Pixel& p : img) {
        auto v = static_cast<std::uint8_t>(low + (high - low) * i / (n - 1));
        p = pack(v, v, v);
        ++i;
    }
    return img;
}

static void day1() {
    Pixel p = pack(0x12, 0x34, 0x56, 0x78);
    CHECK(p.value == 0x12345678u);
    CHECK(pack(255, 0, 0).value == 0xFF0000FFu);
    CHECK(red(p) == 0x12 && green(p) == 0x34 && blue(p) == 0x56 && alpha(p) == 0x78);
    Pixel q = invertRGB(p);
    CHECK(red(q) == 0xED && green(q) == 0xCB && blue(q) == 0xA9 && alpha(q) == 0x78);
    CHECK(invertRGB(q) == p);
    CHECK(flipChannelBits(flipChannelBits(p, 0x0F0F0F00u), 0x0F0F0F00u) == p);
    CHECK(flipChannelBits(p, 0xFF000000u).value == 0xED345678u);
    CHECK(isOddRed(pack(3, 0, 0)));
    CHECK(!isOddRed(pack(4, 1, 1)));
    CHECK(remainderPow2(27, 8) == 3);
    CHECK(remainderPow2(27, 2) == 1);
    CHECK(remainderPow2(27, 1) == 0);
}
static void day2() {
    CHECK(FORGE_SQUARE(2 + 1) == 9);
    CHECK(10 - FORGE_MAX(1, 2) == 8);
    CHECK(FORGE_CLAMP(300, 0, 255) == 255);
    CHECK(FORGE_CLAMP(-4, 0, 255) == 0);
    CHECK(FORGE_CLAMP(4 + 1, 0, 255) == 5);
    CHECK(countEvaluations() == 2);
    int n = 299;
    CHECK(clampByte(++n) == 255 && n == 300);
    CHECK(clampByte(-1) == 0);
    CHECK(clampByte(128) == 128);
}
static void day3() {
    int before = Pixel::liveArrays;
    {
        Pixel blue_ = pack(0, 0, 255);
        Image img(4, 3, blue_);
        CHECK(img.width() == 4 && img.height() == 3 && img.size() == 12);
        CHECK(img.at(3, 2) == blue_);
        img.at(1, 2) = pack(1, 2, 3);
        CHECK(img.row(2)[1] == pack(1, 2, 3));
        CHECK(img.row(1) - img.row(0) == 4);
        CHECK(img.end() - img.begin() == 12);
        CHECK_THROWS(img.at(4, 0), std::out_of_range);
        CHECK_THROWS(img.at(0, -1), std::out_of_range);
        const Image& view = img;
        CHECK(view.at(1, 2) == pack(1, 2, 3));
        CHECK(view.row(2)[1] == pack(1, 2, 3));
        CHECK(Pixel::liveArrays == before + 1);
    }
    CHECK(Pixel::liveArrays == before);
    CHECK_THROWS(Image(-1, 5), std::invalid_argument);
}
static void day5() {
    int before = Pixel::liveArrays;
    {
        Image a(3, 2, pack(9, 9, 9));
        Image b(a);
        CHECK(sameImage(a, b));
        b.at(0, 0) = pack(1, 1, 1);
        CHECK(a.at(0, 0) == pack(9, 9, 9));

        Image c(1, 1);
        c = a;
        CHECK(sameImage(a, c) && c.begin() != a.begin());
        Image& self = c;
        c = self;
        CHECK(sameImage(a, c));

        Pixel* where = a.begin();
        Image d(std::move(a));
        CHECK(d.begin() == where && a.empty() && a.width() == 0);

        Image e(2, 2);
        e = std::move(d);
        CHECK(e.begin() == where && d.empty());
        CHECK(Pixel::liveArrays == before + 3);
    }
    CHECK(Pixel::liveArrays == before);
}
static std::string bytesOf(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
}
static void day6() {
    CHECK(bmpRowBytes(1) == 4);
    CHECK(bmpRowBytes(2) == 8);
    CHECK(bmpRowBytes(3) == 12);
    CHECK(bmpRowBytes(4) == 12);
    const char* path = "forge_day6.bmp";
    Image img(2, 2);
    img.at(0, 0) = pack(10, 20, 30);
    img.at(1, 0) = pack(40, 50, 60);
    img.at(0, 1) = pack(70, 80, 90);
    img.at(1, 1) = pack(100, 110, 120);
    saveBmp(img, path);
    std::string b = bytesOf(path);
    std::remove(path);
    CHECK(b.size() == 70);
    if (b.size() == 70) {
        CHECK(b[0] == 'B' && b[1] == 'M');
        CHECK(static_cast<unsigned char>(b[2]) == 70);
        CHECK(b[10] == 54 && b[14] == 40 && b[18] == 2 && b[22] == 2 && b[26] == 1 && b[28] == 24);
        CHECK(b[54] == 90 && b[55] == 80 && b[56] == 70);   // bottom row comes first, as BGR
        CHECK(b[62] == 30 && b[63] == 20 && b[64] == 10);   // then the top row
    }
    CHECK_THROWS(saveBmp(img, "no_such_folder_xyz/a.bmp"), std::runtime_error);
}
static void day7() {
    const char* path = "forge_day7.bmp";
    Image img = sample();
    saveBmp(img, path);
    Image back = loadBmp(path);
    CHECK(sameImage(img, back));
    {   // a 1 by 1, 32-bit BMP: blue 30, green 20, red 10
        std::ofstream f(path, std::ios::binary);
        f.put('B'); f.put('M');
        writeLE(f, 58, 4); writeLE(f, 0, 4); writeLE(f, 54, 4); writeLE(f, 40, 4);
        writeLE(f, 1, 4); writeLE(f, 1, 4); writeLE(f, 1, 2); writeLE(f, 32, 2);
        for (int i = 0; i < 6; ++i) writeLE(f, 0, 4);
        f.put(30); f.put(20); f.put(10); f.put(static_cast<char>(255));
    }
    CHECK(loadBmp(path).at(0, 0) == pack(10, 20, 30));
    std::ofstream(path, std::ios::binary) << "XX not a bitmap";
    CHECK_THROWS(loadBmp(path), std::runtime_error);
    std::remove(path);
    CHECK_THROWS(loadBmp("no_such_file_xyz.bmp"), std::runtime_error);
}
static void day8() {
    Image a = sample(), b = sample();
    invert(a);
    CHECK(a.at(2, 1) == invertRGB(b.at(2, 1)));
    invert(a);
    CHECK(sameImage(a, b));
    CHECK(!isGrayscale(a));
    grayscale(a);
    CHECK(isGrayscale(a));
    CHECK(red(a.at(1, 1)) == luma(b.at(1, 1)));
    Image c = grayRamp(10, 10, 0, 255);
    threshold(c, 128);
    CHECK(c.at(0, 0) == pack(0, 0, 0));
    CHECK(c.at(9, 9) == pack(255, 255, 255));
}
static void day9() {
    CHECK(adjustBrightness(pack(250, 10, 100, 7), 10) == pack(255, 20, 110, 7));
    CHECK(adjustBrightness(pack(5, 10, 100, 7), -10) == pack(0, 0, 90, 7));
    PixelFn up = brightness(20);
    CHECK(up(pack(1, 2, 3)) == pack(21, 22, 23));
    CHECK(tint(0.5, 1.0, 2.0)(pack(100, 100, 100)) == pack(50, 100, 200));
    Image img(2, 2, pack(100, 100, 100));
    applyAll(img, {brightness(50), tint(0.5, 0.5, 0.5)});
    CHECK(img.at(1, 1) == pack(75, 75, 75));
    Image ramp = grayRamp(10, 1, 0, 90);
    CHECK(countWithRef(ramp, 50) == 5);
}
static void day10() {
    Image img(3, 2, pack(10, 10, 10));
    img.at(0, 0) = pack(200, 200, 200);
    Histogram h = histogram(img);
    CHECK(h[10] == 5 && h[200] == 1 && h[0] == 0);
    CHECK(countBright(img, 100) == 1);
    CHECK(meanLuma(h) > 41.6 && meanLuma(h) < 41.7);
    Histogram none{};
    CHECK(meanLuma(none) == 0.0);
    auto bright = selectBright(img, 100);
    CHECK(bright.size() == 1 && bright[0] == pack(200, 200, 200));
}
static void day12() {
    Histogram h{};
    h[2] = 3; h[5] = 4; h[255] = 1;
    auto c = cumulative(h);
    CHECK(c[1] == 0 && c[2] == 3 && c[4] == 3 && c[5] == 7 && c[255] == 8);
    Image img = grayRamp(50, 50, 100, 140);
    equalize(img);
    auto hi = histogram(img);
    CHECK(hi[0] > 0 && hi[255] > 0);
    Image flat(4, 4, pack(77, 77, 77));
    equalize(flat);
    CHECK(flat.at(2, 2) == pack(77, 77, 77));
}
static void day13() {
    int w[] = {1, 2, 3}, s[] = {4, 5, 6};
    CHECK(weightedSum(w, s, 3) == 32);
    static const int identity[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    Image img = sample();
    CHECK(sameImage(convolve(img, identity, 1), img));
    Image flat(5, 5, pack(80, 90, 100));
    CHECK(sameImage(blur(flat), flat));
    CHECK(sameImage(sharpen(flat), flat));
    Image dot(5, 5, pack(0, 0, 0));
    dot.at(2, 2) = pack(160, 160, 160);
    Image soft = blur(dot);
    CHECK(soft.at(2, 2) == pack(40, 40, 40));
    CHECK(soft.at(1, 1) == pack(10, 10, 10));
    CHECK(soft.at(0, 0) == pack(0, 0, 0));
}
static void day14() {
    CHECK(medianOf({9, 1, 8, 2, 7, 3, 6, 4, 5}) == 5);
    Image img(5, 5, pack(50, 60, 70));
    img.at(2, 2) = pack(255, 255, 255);
    Image out = medianFilter(img);
    CHECK(sameImage(out, Image(5, 5, pack(50, 60, 70))));
    Image ramp = grayRamp(4, 1, 0, 30);
    auto top = topLumas(ramp, 2);
    CHECK(top.size() == 2 && top[0] == 30 && top[1] == 20);
    CHECK(topLumas(ramp, 99).size() == 4);
}
static void day15() {
    InvertFilter f;
    Named& viaFilter = static_cast<Filter&>(f);
    Named& viaTimed = static_cast<Timed&>(f);
    CHECK(&viaFilter == &viaTimed);       // one shared Named subobject
    CHECK(viaFilter.name() == "invert");
    Image a = sample(), b = sample();
    Filter& asFilter = f;
    asFilter.apply(a);
    asFilter.apply(a);
    CHECK(sameImage(a, b));
    Timed& asTimed = f;
    CHECK(asTimed.calls() == 2);
    CHECK(asTimed.totalMicros() >= 0);
    CHECK(asTimed.report() == "invert: 2 calls");
}
static void day16() {
    int before = Stack<int>::liveNodes();
    {
        Stack<int> s;
        CHECK(s.empty());
        s.push(3); s.push(5); s.push(9);
        CHECK(s.size() == 3 && s.top() == 9);
        CHECK(s.pop() == 9 && s.pop() == 5);
        CHECK(s.size() == 1);
        s.push(1); s.push(2);
        CHECK(Stack<int>::liveNodes() == before + 3);
    }
    CHECK(Stack<int>::liveNodes() == before);
    Stack<std::string> t;
    CHECK_THROWS(t.pop(), std::out_of_range);
    CHECK_THROWS(t.top(), std::out_of_range);
    t.push("a"); t.push("b");
    t.clear();
    CHECK(t.empty() && t.size() == 0);
}
static void day17() {
    Image first(2, 2, pack(1, 1, 1));
    History h(first);
    CHECK(!h.undo() && !h.redo());
    h.commit(Image(2, 2, pack(2, 2, 2)));
    h.commit(Image(2, 2, pack(3, 3, 3)));
    CHECK(h.undoCount() == 2);
    ImagePtr held = h.current();
    CHECK(held.use_count() == 2);
    CHECK(h.undo());
    CHECK(h.current()->at(0, 0) == pack(2, 2, 2));
    CHECK(h.redoCount() == 1);
    CHECK(held.use_count() == 2);        // redoStack and held share it
    CHECK(h.redo());
    CHECK(h.current() == held);
    h.undo();
    h.commit(Image(2, 2, pack(4, 4, 4)));
    CHECK(h.redoCount() == 0);
    CHECK(held.use_count() == 1);        // only held still owns it
    auto f = makeFilter("grayscale");
    CHECK(f->name() == "grayscale");
    Image img = sample();
    f->apply(img);
    CHECK(isGrayscale(img));
    CHECK_THROWS(makeFilter("nope"), std::invalid_argument);
}
static void day19() {
    Queue<int> q;
    CHECK(q.empty());
    q.push(3); q.push(5); q.push(9);
    CHECK(q.size() == 3 && q.pop() == 3 && q.pop() == 5 && q.pop() == 9);
    CHECK(q.empty());
    CHECK_THROWS(q.pop(), std::out_of_range);
    q.push(7);
    CHECK(q.pop() == 7);
    Recent r(2);
    r.add("a"); r.add("b"); r.add("c");
    CHECK(r.size() == 2 && r.at(0) == "c" && r.at(1) == "b");
    std::list<Pixel> px{pack(5, 5, 5), pack(200, 200, 200), pack(6, 6, 6), pack(7, 7, 7), pack(250, 250, 250)};
    removeDark(px, 100);
    CHECK(px.size() == 2 && px.front() == pack(200, 200, 200) && px.back() == pack(250, 250, 250));
    CHECK(reversedWithStack({1, 2, 3}) == std::vector<int>({3, 2, 1}));
}
static void day20() {
    auto t = split("  blur   3  ");
    CHECK(t.size() == 2 && t[0] == "blur" && t[1] == "3");
    CHECK(split("    ").empty());
    CHECK(std::get<int>(parseArg("-12")) == -12);
    CHECK(std::get<double>(parseArg("1.5")) == 1.5);
    CHECK(std::get<std::string>(parseArg("a.bmp")) == "a.bmp");
    CHECK(std::get<std::string>(parseArg("-")) == "-");
    Command c = parseLine("tint 1 0.5 warm");
    CHECK(c.name == "tint" && c.args.size() == 3);
    CHECK(asNumber(c.args[0]) == 1.0 && asNumber(c.args[1]) == 0.5);
    CHECK_THROWS(asNumber(c.args[2]), std::bad_variant_access);
    CHECK_THROWS(parseLine("   "), std::invalid_argument);
    const char* path = "forge_day20.forge";
    { std::ofstream f(path); f << "# comment\n\nblur\n  # indented comment\nbrightness 10\n"; }
    auto script = loadScript(path);
    std::remove(path);
    CHECK(script.size() == 2 && script[1].name == "brightness");
    CHECK_THROWS(loadScript("no_such_file_xyz"), std::runtime_error);
}
static void day21() {
    int** g = allocGrid(2, 3);
    g[1][2] = 7;
    CHECK(g[0][0] == 0 && g[1][2] == 7);
    freeGrid(g, 2);
    Image img(4, 2, pack(0, 0, 0));
    for (int x = 2; x < 4; ++x)
        for (int y = 0; y < 2; ++y) img.at(x, y) = pack(100, 100, 100);
    int** d = downsample(img, 1, 2);
    CHECK(d[0][0] == 0 && d[0][1] == 100);
    freeGrid(d, 1);
    Image black(8, 4, pack(0, 0, 0)), white(8, 4, pack(255, 255, 255));
    CHECK(toAscii(black, 8) == "        \n        \n");
    CHECK(toAscii(white, 8) == "@@@@@@@@\n@@@@@@@@\n");
    CHECK(std::string(levelName(0)) == "black");
    CHECK(std::string(levelName(120)) == "mid");
    CHECK(std::string(levelName(255)) == "white");
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    CHECK(sumFixed(a, 2) == 21);
}
static void day22() {
    auto r = splitRows(10, 3);
    CHECK(r.size() == 3 && r[0] == std::make_pair(0, 4) && r[1] == std::make_pair(4, 7) && r[2] == std::make_pair(7, 10));
    CHECK(splitRows(2, 8).size() == 2);
    CHECK(splitRows(0, 4).empty());
    Image a = grayRamp(300, 200, 0, 200), b = a;
    PixelFn fn = brightness(30);
    applyFn(a, fn);
    parallelApply(b, fn, 4);
    CHECK(sameImage(a, b));
    Image tiny(1, 1, pack(1, 1, 1));
    parallelApply(tiny, fn, 16);
    CHECK(tiny.at(0, 0) == pack(31, 31, 31));
}
static void day23() {
    Image img = grayRamp(200, 150, 0, 255);
    Histogram one = histogram(img);
    CHECK(parallelHistogram(img, 4) == one);
    double m = meanLuma(one);
    CHECK(meanViaPromise(img) == m);
    CHECK(meanViaPackagedTask(img) == m);
}
static void day24() {
    bumpLocal(100);
    auto counts = localCounts(4, 3);
    CHECK(counts.size() == 4);
    for (int c : counts) CHECK(c == 6);   // no thread sees another thread's bumps
    std::vector<int> v(100000);
    std::iota(v.begin(), v.end(), 1);
    CHECK(safeSum(v, 8) == 5000050000LL);
}

void registerDays(std::map<int, std::function<void()>>& d) {
    d[1] = day1;   d[2] = day2;   d[3] = day3;   d[5] = day5;   d[6] = day6;
    d[7] = day7;   d[8] = day8;   d[9] = day9;   d[10] = day10; d[12] = day12;
    d[13] = day13; d[14] = day14; d[15] = day15; d[16] = day16; d[17] = day17;
    d[19] = day19; d[20] = day20; d[21] = day21; d[22] = day22; d[23] = day23;
    d[24] = day24;
}
