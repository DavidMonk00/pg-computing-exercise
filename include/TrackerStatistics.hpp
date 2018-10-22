#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <stdio.h>
#include <chrono>
#include <omp.h>
#include "constants.hpp"
#include "Track.hpp"


class TrackerStatistics {
private:
  char* bytes;
  int number_tracks;
  track_params* track_parameters;
  unsigned concurentThreadsSupported;

public:
  TrackerStatistics();
  ~TrackerStatistics();
  void readFile(std::string filename);
  void fit();
  void getStats();
  void saveData(std::string filename);
};
