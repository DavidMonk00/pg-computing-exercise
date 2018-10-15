#pragma once
#include <cmath>
#include "Hit.hpp"
#include "constants.hpp"

class Line {
private:
  float* x;
  float* y;

public:
  Line (Hit* hit0, Hit* hit1);
  ~Line ();
  float getGradient();
  float* getX();
  float* getY();
  float distanceToPoint(Hit* hit);
};
