#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include "constants.hpp"
#include "Track.hpp"


void threadCallBack(
  std::vector<Track*>* tracks,
  track_params* track_parameters,
  signed concurentThreadsSupported,
  int id
);


class TrackerStatistics {
private:
  std::vector<Track*> tracks;
  int number_tracks;
  track_params* track_parameters;
  unsigned concurentThreadsSupported;

public:
  TrackerStatistics();
  ~TrackerStatistics();
  void readFile(std::string filename);
  void fit();
  void getStats();
};
