#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "constants.hpp"
#include "Track.hpp"

Track** readFile(std::string filename);
