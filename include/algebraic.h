#ifndef ALGEBRAIC_H
#define ALGEBRAIC_H
#include <iostream>
#include <vector>
typedef struct {double x,y; int h,o;} Point;
std::vector<Point> precalc(const int maxh);
#endif
