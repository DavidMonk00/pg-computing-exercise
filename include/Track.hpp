#pragma once
#include <iostream>
#include "constants.hpp"
#include "Hit.hpp"

class Track {
private:
  Hit** hits;

public:
  Track (char* data);
  ~Track ();
};
