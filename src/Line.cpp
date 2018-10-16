#include "Line.hpp"

Line::Line(Hit* hit0, Hit* hit1) {
  x = (float*)malloc(2*sizeof(float));
  y = (float*)malloc(2*sizeof(float));
  x[0] = hit0->getX();
  x[1] = hit1->getX();
  y[0] = hit0->getY();
  y[1] = hit1->getY();
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

float* Line::getX() {
  return x;
}

float* Line::getY() {
  return y;
}

void Line::setY(float y0, float y1) {
  y[0] = y0;
  y[1] = y1;
}

float Line::distanceSquaredToPoint(Hit* hit) {
  float xp = hit->getX();
  float yp = hit->getY();
  float d = ((y[1]-y[0])*xp - (x[1] - x[0])*yp + x[1]*y[0] - y[1]*x[0])*((y[1]-y[0])*xp - (x[1] - x[0])*yp + x[1]*y[0] - y[1]*x[0]) /
            (y[1] - y[0])*(y[1] - y[0]) + (x[1] - x[0])*(x[1] - x[0]);
  return d;
}
