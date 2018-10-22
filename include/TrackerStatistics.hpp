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


struct ThreadParams {
  Track** tracks;
  track_params* track_parameters;
  signed concurentThreadsSupported;
  long id;
};


void* threadCallBack(void* tp);


class TrackerStatistics {
private:
  Track** tracks;
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
