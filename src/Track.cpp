#include "Track.hpp"

Track::Track(char* data) {
  hits = (Hit**)malloc(NUMBER_OF_LAYERS*sizeof(Hit*));
  for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
    char hits_temp[2];
    hits_temp[0] = data[2*i];
    hits_temp[1] = data[2*i+1];
    hits[i] = new Hit(hits_temp);
    hits[i]->printValues();
  }
}

Track::~Track() {}
