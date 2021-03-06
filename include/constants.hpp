/**
  @file constants.hpp
  @brief Defines the constants used throughout the program.
  @author David Monk - Imperial College London
  @version 1.0
*/

#pragma once

#define TRACK_SIZE 16
#define NUMBER_OF_LAYERS 8
#define PI 3.14159265359
#define V_INIT 0.0048
#define V_ALPHA 0.0001
#define P_ALPHA 0.18
#define ERROR_THRESHOLD 0.02*NUMBER_OF_LAYERS//0.017//0.01
#define FILENAME "./data/manytracks.raw"
#define MAX_ITERATIONS 500
#define TOTAL_TRACKS 1e6
#define BATCH_SIZE 1e4
