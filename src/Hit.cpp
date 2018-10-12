#include "Hit.hpp"

Hit::Hit(char* data) {
  unsigned short x_init, y_init, tdc_init;
  unsigned short bits = (unsigned short)((data[1]<<8)^data[0]);
  x_init = bits&0b111;
  y_init = (bits>>3)&0b111;
  y = (float)y_init;
  if (x_init % 2 == 1) {
    y = y + 0.5;
  }
  x = (float)x_init;
  tdc_init = (bits>>6)&0b1111111111;
  tdc = tdc_init*0.5 + 0.25;
}

Hit::~Hit() {}

void Hit::printValues() {
  std::cout << x << " " << y << " " << tdc << '\n';
}
