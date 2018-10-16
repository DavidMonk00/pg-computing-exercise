#include "Track.hpp"

Track::Track(char* data) {
  hits = (Hit**)malloc(NUMBER_OF_LAYERS*sizeof(Hit*));
  for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
    char hits_temp[2];
    hits_temp[0] = data[2*i];
    hits_temp[1] = data[2*i+1];
    hits[i] = new Hit(hits_temp);
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

track_params Track::fit(int N, float v_alpha, float l_alpha) {
  int i, j, counter;
  counter = 0;
  float v = 0.005;
  float y0_prev, y1_prev;
  Line* line = new Line(hits[0], hits[NUMBER_OF_LAYERS-1]);
  float e = 0;
  for (i = 0; i < NUMBER_OF_LAYERS; i++) {
    e += std::abs(hits[i]->getTDC()*v - line->distanceToPoint(hits[i]));
  }
  float e_new;
  while (e/NUMBER_OF_LAYERS > 0.001 ^ counter == 1e5) {
    counter++;
    e_new = 0;
    float v_new = v + v_alpha*getRandomStep();
    y0_prev = line->y[0];
    y1_prev = line->y[1];
    line->y[0] += l_alpha*getRandomStep();
    line->y[1] += l_alpha*getRandomStep();
    for (j = 0; j < NUMBER_OF_LAYERS; j++) {
      e_new += std::abs(hits[j]->getTDC()*v_new - line->distanceToPoint(hits[j]));
    }
    if (e_new < e) {
      e = e_new;
      v = v_new;
    } else {
      line->y[0] = y0_prev;
      line->y[1] = y1_prev;
    }
  }
  track_params t;
  t.gradient = line->getGradient();
  t.v = v;
  delete line;
  return t;
}
