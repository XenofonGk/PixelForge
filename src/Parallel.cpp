#include "Parallel.h"
#include "Common.h"
#include <algorithm>
#include <functional>
#include <future>
#include <numeric>
#include <thread>

// ---- Day 22 ----
std::vector<std::pair<int, int>> splitRows(int height, int parts) {
    // TODO Day 22: give each part height / parts rows, and share the remainder one row at a time among the first parts.
    NOT_IMPLEMENTED();
}
void parallelApply(Image& img, const PixelFn& fn, int threads) {
    // TODO Day 22: start one std::thread per range, each transforming only its own rows, then join them all. Pass fn by std::cref or capture it by reference.
    NOT_IMPLEMENTED();
}

// ---- Day 23 ----
Histogram parallelHistogram(const Image& img, int tasks) {
    // TODO Day 23: launch one std::async per range with std::launch::async. Each task builds its own Histogram. Add the results together using get().
    NOT_IMPLEMENTED();
}
double meanViaPromise(const Image& img) {
    // TODO Day 23: create a std::promise<double>, get its future, and start a thread that calls set_value. Pass the promise with std::ref. Call get(), then join.
    NOT_IMPLEMENTED();
}
double meanViaPackagedTask(const Image& img) {
    // TODO Day 23: wrap the work in std::packaged_task<double(const Image&)>, get its future, run the task, and return get().
    NOT_IMPLEMENTED();
}

// ---- Day 24 ----
// TODO Day 24: make this thread_local, so that each thread gets its own copy.
int localCounter = 0;
int bumpLocal(int times) {
    // TODO Day 24: add times to localCounter and return it.
    NOT_IMPLEMENTED();
}
std::vector<int> localCounts(int threads, int times) {
    // TODO Day 24: start one std::thread per slot of a results vector. Each thread calls bumpLocal(times) twice and stores the second result in its own slot. Join them all.
    NOT_IMPLEMENTED();
}
long long safeSum(const std::vector<int>& values, int tasks) {
    // TODO Day 24: give each async task its own range and let it return its total. Adding to one shared variable from several threads is a race condition.
    NOT_IMPLEMENTED();
}
