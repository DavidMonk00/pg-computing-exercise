#include "main.hpp"

using namespace std;


std::vector<Track*> readFile(string filename) {
  streampos size;
  std::vector<Track*> tracks;
  std::ifstream file(filename, ios::in|ios::binary|ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    int number_tracks = size/TRACK_SIZE;
    file.seekg (0,ios::beg);
    for (int i = 0; i < number_tracks; i++) {
      char track[TRACK_SIZE];
      file.read(track, TRACK_SIZE);
      tracks.push_back(new Track(track));
    }
    file.close();
  } else {
    cout << "Unable to open file" << endl;
  }
  return tracks;
}


void threadCallBack(std::vector<Track*>* tracks, track_params* track_parameters, signed concurentThreadsSupported, int id) {
  for (int i = id; i < tracks->size(); i = i + concurentThreadsSupported) {
    track_parameters[i] = tracks->at(i)->fit(NUMBER_OF_ITERATIONS, V_ALPHA, P_ALPHA);
    if (i % (tracks->size()/100) == 0) {
      std::cout << i << '\n';
    }
  }

}


int main(int argc, char const *argv[]) {
  unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
  std::cout << concurentThreadsSupported << '\n';
  std::srand(std::time(NULL));
  std::vector<Track*> tracks = readFile("./data/manytracks.raw");
  track_params* track_parameters = (track_params*)malloc(tracks.size()*sizeof(track_params));
  std::cout << "File read, starting fitting..." << '\n';
  std::vector<std::thread> threads;
  for (int i = 0; i < concurentThreadsSupported; i++) {
     threads.push_back(std::thread(threadCallBack, &tracks, track_parameters, concurentThreadsSupported, i));
   }
  for (int i = 0; i < concurentThreadsSupported; i++) {
    threads.at(i).join();
    delete tracks[i];
  }
  free(track_parameters);
  return 0;
}
