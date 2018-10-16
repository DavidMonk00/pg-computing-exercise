#include "TrackerStatistics.hpp"

void threadCallBack(
  std::vector<Track*>* tracks,
  track_params* track_parameters,
  signed concurentThreadsSupported,
  int id
)
{
  for (int i = id; i < tracks->size(); i = i + concurentThreadsSupported) {
    track_parameters[i] = tracks->at(i)->fit(NUMBER_OF_ITERATIONS, V_ALPHA, P_ALPHA);
    if (i % (tracks->size()/100) == 0) {
      std::cout << i << '\n';
    }
  }
}

TrackerStatistics::TrackerStatistics() {
  std::srand(std::time(NULL));
  concurentThreadsSupported = std::thread::hardware_concurrency();
  std::cout << "Available threads: " << concurentThreadsSupported << '\n';
}

TrackerStatistics::~TrackerStatistics() {
  for (auto i : tracks) {
    delete i;
  }
  free(track_parameters);
}

void TrackerStatistics::readFile(std::string filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    number_tracks = size/TRACK_SIZE;
    file.seekg (0,std::ios::beg);
    for (int i = 0; i < number_tracks; i++) {
      char track[TRACK_SIZE];
      file.read(track, TRACK_SIZE);
      tracks.push_back(new Track(track));
    }
    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

void TrackerStatistics::fit() {
  track_parameters = (track_params*)malloc(number_tracks*sizeof(track_params));
  std::vector<std::thread> threads;
  for (int i = 0; i < concurentThreadsSupported; i++) {
     threads.push_back(std::thread(threadCallBack, &tracks, track_parameters, concurentThreadsSupported, i));
   }
  for (int i = 0; i < concurentThreadsSupported; i++) {
    threads.at(i).join();
  }
}

void TrackerStatistics::getStats() {
  float g_mean = 0;
  float v_mean = 0;
  for (int i = 0; i < number_tracks; i++) {
    g_mean += track_parameters[i].gradient;
    v_mean += track_parameters[i].v;
  }
  std::cout << g_mean/number_tracks << " " << v_mean/number_tracks << '\n';
}
