#include "main.hpp"

using namespace std;



int main(int argc, char const *argv[]) {
  streampos size;
  char* memblock;
  std::ifstream file ( "./data/manytracks.raw", ios::in|ios::binary|ios::ate );
  if (file.is_open()) {
    size = file.tellg();
    std::cout << size << '\n';
    memblock = new char [size];
    file.seekg (0,ios::beg);
    file.read(memblock, size);
    file.close();
    cout << "the entire file content is in memory";
    delete[] memblock;
  } else {
    cout << "Unable to open file" << endl;
  }
  return 0;
}
