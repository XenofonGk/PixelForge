#ifndef FORGE_PARALLEL_H
#define FORGE_PARALLEL_H
// Days 22 to 24: threads, futures, thread_local storage.
// Notes: G-Performance/multithreading, G-Performance/thread-classes
#include "Filters.h"
#include <utility>
#include <vector>

// ---- Day 22: std::thread ----
// Divide rows 0..height into parts of near-equal size as [first, last) pairs.
// Use fewer parts if there are fewer rows than parts.
std::vector<std::pair<int, int>> splitRows(int height, int parts);
void parallelApply(Image& img, const PixelFn& fn, int threads);

// ---- Day 23: async, promise, packaged_task ----
Histogram parallelHistogram(const Image& img, int tasks); // std::async
double meanViaPromise(const Image& img);                  // std::promise and std::thread
double meanViaPackagedTask(const Image& img);             // std::packaged_task

// ---- Day 24: thread_local and avoiding races ----
int bumpLocal(int times);                       // adds to a thread_local counter, returns it
std::vector<int> localCounts(int threads, int times); // each thread's own final count
long long safeSum(const std::vector<int>& values, int tasks); // no shared writes

#endif
