#!/bin/bash

# Navigate to the src folder
cd "$(dirname "$0")/src" || { echo "Could not find the src directory. Exiting..."; exit 1; }

# Compile and run the shortest_path program
echo
echo "Running Quickest Path System..."
echo
g++ -o shortest_path main.cpp graph.cpp preprocessing.cpp -std=c++17 -pthread
if ./shortest_path data/usa_roads.csv 1 1000000; then
  echo
  echo "Shortest Path System executed successfully."
  echo
else
  echo
  echo "Shortest Path System failed. Exiting..."
  echo
  exit 1
fi