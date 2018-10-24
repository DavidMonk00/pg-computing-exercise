/**
  @file Line.hpp
  @brief Defines the Line class.
  @author David Monk - Imperial College London
  @version 1.0
*/

#pragma once
#include <cmath>
#include <cstdlib>
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
  float distanceToPoint(Hit* hit);
};
