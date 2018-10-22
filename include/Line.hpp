#pragma once
#include <cmath>
#include "Hit.hpp"
#include "constants.hpp"

class Line {
private:


public:
  float* x;
  float* y;

  Line(Hit* hit0, Hit* hit1);
  Line(float* xl, float* yl);
  ~Line();
  float getGradient();
  float* getX();
  float* getY();
  void setY(float y0, float y1);
  float distanceSquaredToPoint(Hit* hit);
};
