/**
  @file Track.cpp
  @brief Defines functions for the Track class.
  @author David Monk - Imperial College London
  @version 1.0
*/

#include "Track.hpp"

/**
   @brief Class constructor.
   @param data - char array of binary data for the track.
*/
Track::Track(char* data) {
  hits = (Hit**)malloc(NUMBER_OF_LAYERS*sizeof(Hit*));
  for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
    hits[i] = new Hit;
    unsigned short x_init, y_init, tdc_init;
    unsigned short bits = (unsigned short)((data[2*i+1]<<8)^(data[2*i]&0xff));
    x_init = bits&0b111;
    y_init = (bits>>3)&0b111;
    hits[i]->y = (float)y_init;
    if (x_init % 2 == 1) {
      hits[i]->y = hits[i]->y + 0.5;
    }
    hits[i]->x = (float)x_init;
    tdc_init = (bits>>6);
    hits[i]->tdc = (float)tdc_init*0.5 + 0.25;
  }
}

/**
   @brief Class destructor.
*/
Track::~Track() {
  for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
    delete hits[i];
  }
  free(hits);
}

/**
   @brief Get a random float between -1 and 1.
   @return Random float in range.
*/
float getRandomStep() {
  return 2*(float)std::rand()/RAND_MAX - 1;
}

/**
   @brief Fit a line to the Hit objects.
   @return Pointer to track_params object containing the gradient of the track and the drift velocity.
*/
track_params* Track::fit() {
  track_params* tp = new track_params;
  int i, j, counter;
  counter = 0;
  float v = V_INIT, y0_prev, y1_prev, e = 0, e_new, v_new;
  Line* line = new Line(hits[0], hits[NUMBER_OF_LAYERS-1]);
  for (i = 0; i < NUMBER_OF_LAYERS; i++) {
    e += std::abs(hits[i]->tdc*v - line->distanceToPoint(hits[i]));
  }
  while (e > ERROR_THRESHOLD) {
    e_new = 0;
    v_new = v + V_ALPHA*getRandomStep();
    v_new = (v_new > 0) ? v_new : v;
    y0_prev = line->y[0];
    y1_prev = line->y[1];
    line->y[0] += P_ALPHA*getRandomStep();
    line->y[1] += P_ALPHA*getRandomStep();
    for (j = 0; j < NUMBER_OF_LAYERS; j++) {
      e_new += std::abs(hits[j]->tdc*v_new - line->distanceToPoint(hits[j]));
    }
    if (e_new < e) {
      e = e_new;
      v = v_new;
    } else {
      line->y[0] = y0_prev;
      line->y[1] = y1_prev;
    }
    if (counter == MAX_ITERATIONS) {
      //std::cout << "Counter: " << counter << "\n";
      return tp;
    }
    counter++;
  }
  //std::cout << "Counter: " << counter << "\n"; // << e/NUMBER_OF_LAYERS << '\n';
  tp->gradient = line->getGradient();
  tp->v = v;
  delete line;
  return tp;
}
