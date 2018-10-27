/**
  @file Line.cpp
  @brief Defines functions for the Line class.
  @author David Monk - Imperial College London
  @version 1.0
*/

#include "Line.hpp"

/**
   @brief Class constructor.
   @param hit0 - Hit object to define the start of the line.
   @param hit1 - Hit object to define the end of the line.
*/
Line::Line(Hit* hit0, Hit* hit1) {
  x = (float*)malloc(2*sizeof(float));
  y = (float*)malloc(2*sizeof(float));
  x[0] = hit0->x;
  x[1] = hit1->x;
  y[0] = hit0->y;
  y[1] = hit1->y;
}

/**
   @brief Class destructor.
*/
Line::~Line() {
  free(x);
  free(y);
}

/**
   @brief Get the gradient of the line.
   @return Gradient of line in degrees as a float.
*/
float Line::getGradient() {
  float dy = y[1] - y[0];
  float dx = x[1] - x[0];
  return std::atan(dy/dx)*180/PI;
}

/**
   @brief Get the perpendicular distance of a point from the line.
   @param hit - Hit object for point to measure from.
   @return Float of distance from the line.
*/
float Line::distanceToPoint(Hit* hit) {
  float xp = hit->x;
  float yp = hit->y;
  float num = (x[1] - x[0])*(y[0] - yp) - (x[0] - xp)*(y[1] - y[0]);
  float den = (y[1] - y[0])*(y[1] - y[0]) + (x[1] - x[0])*(x[1] - x[0]);
  float d = std::abs(num) / std::sqrt(den);
  return d;
}
