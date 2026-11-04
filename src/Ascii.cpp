#include "Ascii.h"
#include "Common.h"
#include "Filters.h"

int** allocGrid(int rows, int cols) {
    // TODO Day 21: allocate an array of int*, then one int array per row, set to zero.
    NOT_IMPLEMENTED();
}
void freeGrid(int** grid, int rows) {
    // TODO Day 21: delete each row with delete[], then the array of pointers.
    NOT_IMPLEMENTED();
}
int** downsample(const Image& img, int rows, int cols) {
    // TODO Day 21: use allocGrid. A pixel (x, y) belongs to cell (y * rows / height, x * cols / width). Each cell holds the mean luma.
    NOT_IMPLEMENTED();
}
std::string toAscii(const Image& img, int cols) {
    // TODO Day 21: rows = cols * height / width / 2, at least 1. Map each cell with the ramp " .:-=+*#%@" using value * 10 / 256. End each row with a newline, and free the grid.
    NOT_IMPLEMENTED();
}
const char* levelName(int lumaValue) {
    // TODO Day 21: store the five names in a ragged array (an array of const char*). Each band is 52 values wide, and band 4 includes 255.
    NOT_IMPLEMENTED();
}
int sumFixed(const int a[][3], int rows) {
    // TODO Day 21: add up every element. Notice why the column count must be in the parameter.
    NOT_IMPLEMENTED();
}
