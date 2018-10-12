#pragma once
#include <iostream>

class Hit {
private:
  float x,y,tdc;

public:
  Hit (char* data);
  ~Hit ();
  void printValues();
};
