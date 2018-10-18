#!/usr/bin/env bash

make clean
make
echo "Running..."
time ./bin/main #| awk '/Counter/ {print $2 > "./data/count";}'
echo "Analysing..."
python analyse.py
