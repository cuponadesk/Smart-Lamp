#ifndef POINT_H
#define POINT_H

#include <stdint.h>

class Point {
  public:
  Point(int8_t a, int8_t b) : x(a), y(b){};
  int8_t x;
  int8_t y;
};

#endif