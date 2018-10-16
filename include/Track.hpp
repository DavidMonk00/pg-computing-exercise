#pragma once
#include <iostream>
#include <cstdlib>
#include "constants.hpp"
#include "Hit.hpp"
#include "Line.hpp"

struct track_params {
  float gradient;
  float v;
};

class Track {
private:
  Hit** hits;

public:
  Track (char* data);
  ~Track ();
  track_params fit(int N, float v_alpha, float l_alpha);
};
