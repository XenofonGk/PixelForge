#ifndef FORGE_FILTER_CLASSES_H
#define FORGE_FILTER_CLASSES_H
// Day 15: multiple inheritance and virtual base classes.
// Notes: H-Deeper-Detail/multiple-inheritance
//
//   Named is the base of both Filter and Timed.
//   TimedFilter inherits from Filter and Timed, which makes a diamond.
//
// As written, a TimedFilter holds two Named subobjects. Your job is to make it hold one.
#include "Filters.h"
#include <string>

class Named {
    std::string label;
protected:
    explicit Named(const std::string& n) : label(n) {}
public:
    virtual ~Named() = default;
    const std::string& name() const { return label; }
};

// TODO Day 15 (part 1): make Filter and Timed inherit Named virtually.
class Filter : public Named {
protected:
    explicit Filter(const std::string& n) : Named(n) {}
public:
    virtual void apply(Image& img) = 0;
};

class Timed : public Named {
    int count{0};
    long long micros{0};
protected:
    explicit Timed(const std::string& n) : Named(n) {}
    void record(long long us) { ++count; micros += us; }
public:
    int calls() const { return count; }
    long long totalMicros() const { return micros; }
    std::string report() const;   // example: "invert: 3 calls"
};

class TimedFilter : public Filter, public Timed {
protected:
    // TODO Day 15 (part 2): with a virtual base, the most-derived class must
    // call Named's constructor directly. Add it here and in the classes below.
    explicit TimedFilter(const std::string& n) : Filter(n), Timed(n) {}
    virtual void run(Image& img) = 0;
public:
    void apply(Image& img) override;   // time run() with steady_clock, then record()
};

class InvertFilter : public TimedFilter {
public:
    InvertFilter() : TimedFilter("invert") {}
protected:
    void run(Image& img) override { invert(img); }
};

class GrayscaleFilter : public TimedFilter {
public:
    GrayscaleFilter() : TimedFilter("grayscale") {}
protected:
    void run(Image& img) override { grayscale(img); }
};

#endif
