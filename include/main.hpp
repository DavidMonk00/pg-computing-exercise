#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <array>
#include <thread>
#include "constants.hpp"
#include "Track.hpp"

std::vector<Track*> readFile(std::string filename);
