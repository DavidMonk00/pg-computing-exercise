#include "main.hpp"

using namespace std;


Track** readFile(string filename) {
  streampos size;
  Track** tracks;
  std::ifstream file(filename, ios::in|ios::binary|ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    int number_tracks = size/TRACK_SIZE;
    tracks = (Track**)malloc(number_tracks*sizeof(Track*));
    file.seekg (0,ios::beg);
    for (int i = 0; i < number_tracks; i++) {
      char track[TRACK_SIZE];
      file.read(track, TRACK_SIZE);
      tracks[i] = new Track(track);
    }
    file.close();
  } else {
    cout << "Unable to open file" << endl;
  }
  return tracks;
}


int main(int argc, char const *argv[]) {
  Track** tracks = readFile("./data/manytracks.raw");
  std::cout << "Done" << '\n';
  return 0;
}
