#include "Line.hpp"

Line::Line(Hit* hit0, Hit* hit1) {
  x = (float*)malloc(2*sizeof(float));
  y = (float*)malloc(2*sizeof(float));
  x[0] = hit0->x;
  x[1] = hit1->x;
  y[0] = hit0->y;
  y[1] = hit1->y;
}

Line::Line(float* xl, float* yl){
  x = (float*)malloc(2*sizeof(float));
  y = (float*)malloc(2*sizeof(float));
  x[0] = xl[0];
  x[1] = xl[1];
  y[0] = yl[0];
  y[1] = yl[1];
}

Line::~Line() {
  free(x);
  free(y);
}

float Line::getGradient() {
  float dy = y[1] - y[0];
  float dx = x[1] - x[0];
  return std::atan(dy/dx)*180/PI;
}

void Line::setY(float y0, float y1) {
  y[0] = y0;
  y[1] = y1;
}

float Line::distanceSquaredToPoint(Hit* hit) {
  float xp = hit->x;
  float yp = hit->y;
  float num = (x[1] - x[0])*(y[0] - yp) - (x[0] - xp)*(y[1] - y[0]);
  float den = (y[1] - y[0])*(y[1] - y[0]) + (x[1] - x[0])*(x[1] - x[0]);
  float d = std::abs(num) / std::sqrt(den);
  return d;
}
