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
public:
  float* x;
  float* y;

  Line(Hit* hit0, Hit* hit1);
  ~Line();
  float getGradient();
  float distanceToPoint(Hit* hit);
};
