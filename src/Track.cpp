#include "Track.hpp"

Track::Track(char* data) {
  hits = (Hit**)malloc(NUMBER_OF_LAYERS*sizeof(Hit*));
  for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
    hits[i] = new Hit(&data[2*i]);
    //hits[i]->printValues();
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

void Track::fit(track_params* track_parameters, int id) {
  int i, j, counter;
  counter = 0;
  float v = V_INIT;
  float y0_prev, y1_prev;
  Line* line = new Line(hits[0], hits[NUMBER_OF_LAYERS-1]);
  float e = 0;
  float tdc;
  for (i = 0; i < NUMBER_OF_LAYERS; i++) {
    tdc = hits[i]->getTDC();
    e += std::abs(tdc*v - line->distanceSquaredToPoint(hits[i]));
  }
  float e_new;
  float v_new;
  while (e/NUMBER_OF_LAYERS > ERROR_THRESHOLD) {
    e_new = 0;
    v_new = v + V_ALPHA*getRandomStep();
    v_new = (v_new > 0) ? v_new : v;
    y0_prev = line->y[0];
    y1_prev = line->y[1];
    line->y[0] += P_ALPHA*getRandomStep();
    line->y[1] += P_ALPHA*getRandomStep();
    for (j = 0; j < NUMBER_OF_LAYERS; j++) {
      tdc = hits[j]->getTDC();
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
      return;
    }
    counter++;
  }
  //std::cout << "Counter: " << counter << "\n"; // << e/NUMBER_OF_LAYERS << '\n';
  //std::cout << line.getGradient() << " " << v << "\n";
  track_parameters[id].gradient = line->getGradient();
  track_parameters[id].v = v;
  delete line;
  //std::cout << "Final error: " << e/NUMBER_OF_LAYERS << '\n';
}
