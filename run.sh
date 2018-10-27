#!/usr/bin/env bash

# p_vals=(0.21 0.22 0.23 0.2415.9)
# for i in "${p_vals[@]}"
# do
#   echo "P_ALPHA=$i"
#   make clean
#   sed -i "8s/.*/#define P_ALPHA $i/" ./include/constants.hpp
#   make
#   echo "Running..."
#   time ./bin/main | awk '/Counter/ {print $2 > "./data/count";}'
#   echo "Analysing..."
#   python analyse.py
# done

make clean
make
echo "Running..."
time ./bin/main #| awk '/Counter/ {print $2 > "./data/count";}'
echo "Analysing..."
time python analyse.py plot
