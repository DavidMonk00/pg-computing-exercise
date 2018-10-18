#pragma once
#include <iostream>
#include <chrono>
#include "constants.hpp"
#include "Track.hpp"
#include "TrackerStatistics.hpp"

std::vector<Track*> readFile(std::string filename);
