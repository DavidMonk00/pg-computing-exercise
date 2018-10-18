#include "main.hpp"

int main(int argc, char const *argv[]) {
  TrackerStatistics* ts = new TrackerStatistics();
  ts->readFile("./data/manytracks.raw");
  ts->fit();
  //ts->getStats();
  ts->saveData("./data/output.csv");
  delete ts;
  return 0;
}
