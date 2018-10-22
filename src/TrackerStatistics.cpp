#include "TrackerStatistics.hpp"

TrackerStatistics::TrackerStatistics() {
  std::srand(std::time(NULL));
  concurentThreadsSupported = 1;//std::thread::hardware_concurrency();
  //std::cout << "Available threads: " << concurentThreadsSupported << '\n';
}

TrackerStatistics::~TrackerStatistics() {
  free(track_parameters);
}

void TrackerStatistics::readFile(std::string filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    number_tracks = size/TRACK_SIZE;
    file.seekg (0,std::ios::beg);
    bytes = (char*)malloc(size*sizeof(char));
    file.read(bytes, size);
    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

void TrackerStatistics::fit() {
  track_parameters = (track_params*)malloc(number_tracks*sizeof(track_params));
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    // auto start = std::chrono::high_resolution_clock::now();
    Track track = Track(&bytes[i*TRACK_SIZE]);
    // auto finish = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = finish - start;
    // std::cout << "Elapsed time to create Track object: " << elapsed.count() << " s\n";
    // start = std::chrono::high_resolution_clock::now();
    track.fit(track_parameters, i);
    // finish = std::chrono::high_resolution_clock::now();
    // elapsed = finish - start;
    // std::cout << "Elapsed time to fit track: " << elapsed.count() << " s\n";
  }
}

void TrackerStatistics::getStats() {
  float g_mean = 0;
  float v_mean = 0;
  //std::cout << "Running analysis..." << '\n';
  for (int i = 0; i < number_tracks; i++) {
    g_mean += track_parameters[i].gradient;
    v_mean += track_parameters[i].v;
  }
  std::cout << g_mean/number_tracks << " " << v_mean/number_tracks << '\n';
}

void TrackerStatistics::saveData(std::string filename) {
  std::ofstream myfile (filename);
  char buff[64];
  if (myfile.is_open()) {
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      snprintf(buff, sizeof buff, "%f,%f\n", track_parameters[i].gradient, track_parameters[i].v);
      myfile << buff;
    }
    myfile.close();
  }
  else std::cout << "Unable to open file";
}
