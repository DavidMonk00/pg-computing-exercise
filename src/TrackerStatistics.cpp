/**
  @file TrackerStatistics.cpp
  @brief Defines functions for the TrackerStatistics class.
  @author David Monk - Imperial College London
  @version 1.1
*/

#include "TrackerStatistics.hpp"

/**
   @brief Class constructor. Seeds random number generator.
*/
TrackerStatistics::TrackerStatistics() {
  number_of_batches = (int)(TOTAL_TRACKS/BATCH_SIZE);
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
   @brief Allocate memory for both the track objects and returned parameters.
*/
void TrackerStatistics::initialiseMemory() {
  track_parameters = (track_params**)malloc(TOTAL_TRACKS*sizeof(track_params*));
}


/**
   @brief Iterate through all tracks and perform the fitting algorithm.
*/
void TrackerStatistics::fit() {
  int number_tracks = TOTAL_TRACKS;
  int i,j;
  //#pragma omp parallel for
  for (i = 0; i < number_of_batches; i++) {
    for (j = 0; j < BATCH_SIZE; j++) {
      Track* track = new Track(&bytes[(int)((i*BATCH_SIZE + j)*TRACK_SIZE)]);
      track_parameters[(int)((i*BATCH_SIZE + j))] = track->fit();
      delete track;
    }
  }
}

/**
   @brief Write the track parameters to a binary file.
   @param filename - String of the filenmae to be written to.
*/
void TrackerStatistics::saveData(std::string filename) {
  std::ofstream fout("./data/out.binary", std::ios::out|std::ios::binary);
  if (fout.is_open()) {
    int i,j;
    for (i = 0; i < number_of_batches; i++) {
      for (j = 0; j < BATCH_SIZE; j++) {
        fout.write(reinterpret_cast<char *>(track_parameters[(int)((i*BATCH_SIZE + j))]), sizeof(*track_parameters[(int)((i*BATCH_SIZE + j))]));
      }
    }
  }
  fout.close();
}
