/**
  @file TrackerStatistics.cpp
  @brief Defines functions for the TrackerStatistics class.
  @author David Monk - Imperial College London
  @version 1.0
*/

#include "TrackerStatistics.hpp"

/**
   @brief Class constructor. Seeds random number generator.
*/
TrackerStatistics::TrackerStatistics() {
  std::srand(std::time(NULL));
  concurentThreadsSupported = 1;//std::thread::hardware_concurrency();
  std::cout << "Available threads: " << concurentThreadsSupported << '\n';
}

/**
   @brief Class destructor.
*/
TrackerStatistics::~TrackerStatistics() {
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    delete track_parameters[i];
  }
  free(track_parameters);
}

/**
   @brief Read binary data into memory.
   @param filename - String of the filenmae to be read.
*/
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

/**
   @brief Iterate through all tracks and perform the fitting algorithm.
*/
void TrackerStatistics::fit() {
  track_parameters = (track_params**)malloc(TOTAL_TRACKS*sizeof(track_params*));
  int number_tracks = TOTAL_TRACKS;
  //#pragma omp parallel for
  for (int i = 0; i < number_tracks; i++) {
    //sleep(1);
    Track* track = new Track(&bytes[i*TRACK_SIZE]);
    track_parameters[i] = track->fit();
    delete track;
  }
}

/**
   @brief Write the track parameters to a binary file.
   @param filename - String of the filenmae to be written to.
*/
void TrackerStatistics::saveData(std::string filename) {
  std::ofstream fout("./data/out.binary", std::ios::out|std::ios::binary);
  if (fout.is_open()) {
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      fout.write(reinterpret_cast<char *>(track_parameters[i]), sizeof(*track_parameters[i]));
    }
  }
  fout.close();
}
