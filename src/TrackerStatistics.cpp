#include "TrackerStatistics.hpp"

TrackerStatistics::TrackerStatistics() {
  std::srand(std::time(NULL));
  concurentThreadsSupported = 1;//std::thread::hardware_concurrency();
  std::cout << "Available threads: " << concurentThreadsSupported << '\n';
}

TrackerStatistics::~TrackerStatistics() {
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    delete tracks[i];
  }
  free(tracks);
  free(track_parameters);
}

void TrackerStatistics::readFile(std::string filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open()) {
    file.seekg (0,std::ios::beg);
    tracks = (Track**)malloc(TOTAL_TRACKS*sizeof(Track*));
    bytes = (char*)malloc(TOTAL_TRACKS*TRACK_SIZE*sizeof(char));
    file.read(bytes, TOTAL_TRACKS*TRACK_SIZE);
    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

void TrackerStatistics::fit() {
  track_parameters = (track_params*)malloc(TOTAL_TRACKS*sizeof(track_params));
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    Track track = Track(&bytes[i*TRACK_SIZE]);
    track.fit(track_parameters, i);
  }
}

void TrackerStatistics::getStats() {
  float g_mean = 0;
  float v_mean = 0;
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    g_mean += track_parameters[i].gradient;
    v_mean += track_parameters[i].v;
  }
  std::cout << g_mean/TOTAL_TRACKS << " " << v_mean/TOTAL_TRACKS << '\n';
}

void TrackerStatistics::saveData(std::string filename) {
  std::ofstream myfile (filename);
  char buff[64];
  if (myfile.is_open()) {
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      snprintf(buff, 64, "%f,%f\n", track_parameters[i].gradient, track_parameters[i].v);
      myfile << buff;
    }
    myfile.close();
  }
  else std::cout << "Unable to open file";
}
