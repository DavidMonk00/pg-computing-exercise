#include "TrackerStatistics.hpp"

TrackerStatistics::TrackerStatistics() {
  std::srand(std::time(NULL));
  concurentThreadsSupported = 1;//std::thread::hardware_concurrency();
  std::cout << "Available threads: " << concurentThreadsSupported << '\n';
}

TrackerStatistics::~TrackerStatistics() {
  free(track_parameters);
}

void TrackerStatistics::readFile(std::string filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open()) {
    file.seekg (0,std::ios::beg);
    bytes = (char*)malloc(TOTAL_TRACKS*TRACK_SIZE*sizeof(char));
    file.read(bytes, TOTAL_TRACKS*TRACK_SIZE);
    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

void TrackerStatistics::fit() {
  track_parameters = (track_params*)malloc(TOTAL_TRACKS*sizeof(track_params));
  #pragma omp parallel for
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
  std::ofstream fout("./data/out.binary", std::ios::out|std::ios::binary);
  if (fout.is_open()) {
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      fout.write(reinterpret_cast<char *>(&track_parameters[i]), sizeof(track_parameters[i]));
    }
  }
  fout.close();
}
