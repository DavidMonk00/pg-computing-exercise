#include "main.hpp"

int main(int argc, char const *argv[]) {
  TrackerStatistics* ts = new TrackerStatistics();
  std::cout << "Reading data..." << '\n';
  auto start = std::chrono::high_resolution_clock::now();
  ts->readFile(FILENAME);
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  std::cout << "Fitting..." << '\n';
  start = std::chrono::high_resolution_clock::now();
  ts->fit();
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  //ts->getStats();
  std::cout << "Saving data..." << '\n';
  start = std::chrono::high_resolution_clock::now();
  ts->saveData("./data/output.csv");
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  delete ts;
  return 0;
}
