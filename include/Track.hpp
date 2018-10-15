#pragma once
#include <iostream>
#include <cstdlib>
#include "constants.hpp"
#include "Hit.hpp"
#include "Line.hpp"

class Track {
private:
  Hit** hits;

public:
  Track (char* data);
  ~Track ();
  void fit(int N, float v_alpha, float l_alpha);
};
