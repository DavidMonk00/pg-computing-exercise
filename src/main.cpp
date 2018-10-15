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


int main(int argc, char const *argv[]) {
  std::srand(std::time(NULL));
  std::vector<Track*> tracks = readFile("./data/onetrack.raw");
  for (auto i : tracks) {
    i->fit(1000, 0.001, 0.1);
    delete i;
  }
  return 0;
}
