#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>

class Hit {
private:


public:
  float x,y,tdc;
  Hit (char* data);
  ~Hit ();
  void printValues();
  float getX();
  float getY();
  float getTDC();
};
