#ifndef FORGE_ASCII_H
#define FORGE_ASCII_H
// Day 21: dynamic 2-D arrays, ragged arrays, passing 2-D arrays to functions.
// Notes: H-Deeper-Detail/arrays-and-pointers
#include "Image.h"
#include <string>

int** allocGrid(int rows, int cols);            // an array of row pointers
void freeGrid(int** grid, int rows);
int** downsample(const Image& img, int rows, int cols); // mean luma per cell
std::string toAscii(const Image& img, int cols);
const char* levelName(int lumaValue);           // ragged array: black, dark, mid, light, white
int sumFixed(const int a[][3], int rows);       // total of an r by 3 array

#endif
