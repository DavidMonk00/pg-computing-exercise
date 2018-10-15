#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>

class Hit {
private:
  float x,y,tdc;

public:
  Hit (char* data);
  ~Hit ();
  void printValues();
  float getX();
  float getY();
  float getTDC();
};
