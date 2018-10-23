#include "Track.hpp"

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

Track::~Track() {
  for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
    delete hits[i];
  }
  free(hits);
}

float getRandomStep() {
  return 2*(float)std::rand()/RAND_MAX - 1;
}

track_params* Track::fit() {
  track_params* tp = new track_params;
  int i, j, counter;
  counter = 0;
  float v = V_INIT;
  float y0_prev, y1_prev;
  Line* line = new Line(hits[0], hits[NUMBER_OF_LAYERS-1]);
  float e = 0;
  float tdc;
  for (i = 0; i < NUMBER_OF_LAYERS; i++) {
    tdc = hits[i]->tdc;
    e += std::abs(tdc*v - line->distanceSquaredToPoint(hits[i]));
  }
  float e_new;
  float v_new;
  while (e > ERROR_THRESHOLD) {
    e_new = 0;
    v_new = v + V_ALPHA*getRandomStep();
    v_new = (v_new > 0) ? v_new : v;
    y0_prev = line->y[0];
    y1_prev = line->y[1];
    line->y[0] += P_ALPHA*getRandomStep();
    line->y[1] += P_ALPHA*getRandomStep();
    for (j = 0; j < NUMBER_OF_LAYERS; j++) {
      tdc = hits[j]->tdc;
      e_new += std::abs(tdc*v_new - line->distanceSquaredToPoint(hits[j]));
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
  //std::cout << line.getGradient() << " " << v << "\n";
  tp->gradient = line->getGradient();
  tp->v = v;
  delete line;
  return tp;
  //std::cout << "Final error: " << e/NUMBER_OF_LAYERS << '\n';
}
