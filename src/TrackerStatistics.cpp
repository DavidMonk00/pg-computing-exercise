#include "TrackerStatistics.hpp"

void threadCallBack(
  Track** tracks,
  track_params* track_parameters,
  signed concurentThreadsSupported,
  int id
)
{
  int start = TOTAL_TRACKS * id/concurentThreadsSupported;
  int end = TOTAL_TRACKS * (id + 1)/concurentThreadsSupported;
  std::cout << "Thread ID=" << id << " " << start << " " << end << '\n';
  int i, c=0;
  for (i = start; i < end; i++,c++) {
    tracks[i]->fit(track_parameters, i);
    // if (concurentThreadsSupported > 1) {
    //   if (i % (tracks->size()/100) == 0) {
    //     std::cout << i*100/tracks->size() << "\%" << '\n';
    //   }
    // }
  }
  std::cout << c << '\n';
}

TrackerStatistics::TrackerStatistics() {
  std::srand(std::time(NULL));
  concurentThreadsSupported = 1;//std::thread::hardware_concurrency();
  //std::cout << "Available threads: " << concurentThreadsSupported << '\n';
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
    //size = file.tellg();
    //std::cout << (size == TOTAL_TRACKS*TRACK_SIZE) << '\n';
    file.seekg (0,std::ios::beg);
    tracks = (Track**)malloc(TOTAL_TRACKS*sizeof(Track*));
    bytes = (char*)malloc(TOTAL_TRACKS*TRACK_SIZE*sizeof(char));
    file.read(bytes, TOTAL_TRACKS*TRACK_SIZE);
    char track[TRACK_SIZE];
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      //file.read(track, TRACK_SIZE);
      tracks[i] = new Track(&bytes[i*TRACK_SIZE]);
    }
    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

void TrackerStatistics::fit() {
  track_parameters = (track_params*)malloc(TOTAL_TRACKS*sizeof(track_params));
  std::vector<std::thread> threads;
  if (TOTAL_TRACKS > concurentThreadsSupported) {
    for (int i = 0; i < concurentThreadsSupported; i++) {
       threads.push_back(std::thread(threadCallBack, tracks, track_parameters, concurentThreadsSupported, i));
     }
    for (int i = 0; i < concurentThreadsSupported; i++) {
      threads.at(i).join();
    }
  } else {
    //std::cout << "Running sequentially..." << '\n';
    threadCallBack(tracks, track_parameters, 1, 0);
  }
  //std::cout << "Fit done." << '\n';
}

void TrackerStatistics::getStats() {
  float g_mean = 0;
  float v_mean = 0;
  //std::cout << "Running analysis..." << '\n';
  for (int i = 0; i < TOTAL_TRACKS; i++) {
    g_mean += track_parameters[i].gradient;
    v_mean += track_parameters[i].v;
  }
  std::cout << g_mean/TOTAL_TRACKS << " " << v_mean/TOTAL_TRACKS << '\n';
}

void TrackerStatistics::saveData(std::string filename) {
  std::ofstream myfile (filename);
  if (myfile.is_open()) {
    for (int i = 0; i < TOTAL_TRACKS; i++) {
      myfile << track_parameters[i].gradient << ",";
      myfile << track_parameters[i].v << "\n";
    }
    myfile.close();
  }
  else std::cout << "Unable to open file";
}
