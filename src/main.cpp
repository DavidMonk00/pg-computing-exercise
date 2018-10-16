#include "main.hpp"

using namespace std;


std::vector<Track*> readFile(string filename) {
  streampos size;
  std::vector<Track*> tracks;
  std::ifstream file(filename, ios::in|ios::binary|ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    int number_tracks = size/TRACK_SIZE;
    (Track**)malloc(number_tracks*sizeof(Track*));
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


void threadCallBack(std::vector<Track*>* tracks, unsigned concurentThreadsSupported, int id) {
  for (int i = id; i < tracks->size(); i = i + concurentThreadsSupported) {
    tracks->at(i)->fit(10, 0.001, 0.1);
  }

}


int main(int argc, char const *argv[]) {
  unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
  std::cout << concurentThreadsSupported << '\n';
  std::srand(std::time(NULL));
  std::vector<Track*> tracks = readFile("./data/manytracks.raw");
  std::vector<std::thread> threads;
  for (int i = 0; i < concurentThreadsSupported; i++) {
     threads.push_back(std::thread(threadCallBack, &tracks, concurentThreadsSupported, i));
   }
  for (int i = 0; i < concurentThreadsSupported; i++) {
    threads.at(i).join();
    delete tracks[i];
  }
  return 0;
}
