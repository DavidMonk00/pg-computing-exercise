#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <pthread.h>
#include <omp.h>
#include "constants.hpp"
#include "Track.hpp"

class TrackerStatistics {
private:
  char* bytes;
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
