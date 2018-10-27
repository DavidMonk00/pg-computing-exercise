/**
  @file TrackerStatistics.hpp
  @brief Defines the TrackerStatistics class.
  @author David Monk - Imperial College London
  @version 1.1
*/

#include <fstream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <omp.h>
#include "constants.hpp"
#include "Track.hpp"

class TrackerStatistics {
private:
  char* bytes;
  track_params** track_parameters;
  unsigned concurentThreadsSupported;
  int number_of_batches;

public:
  TrackerStatistics();
  ~TrackerStatistics();
  void readFile(std::string filename);
  void initialiseMemory();
  void fit();
  void saveData(std::string filename);
};
