#pragma once
#include <iostream>
#include <cstdlib>
#include <random>
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
  track_params* fit();
};
