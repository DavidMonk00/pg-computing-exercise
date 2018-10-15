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

Track::~Track() {}

void Track::fit(int N) {
  float v = 0.005;
  Line* line = new Line(hits[0], hits[NUMBER_OF_LAYERS-1]);
  float e = 0;
  for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
    e += std::abs(hits[i]->getTDC()*v - line->distanceToPoint(hits[i]));
  }
  for (int i = 0; i < N; i++) {
    float v_new = v;

  }
  std::cout << RAND_MAX << '\n';
}
