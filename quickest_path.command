#!/bin/bash

# Navigate to the src folder
cd "$(dirname "$0")/src" || { echo "Could not find the src directory. Exiting..."; exit 1; }

# Compile the verification program
echo
echo "Compiling verification program..."
g++ -o verification main_verification.cpp verification.cpp -std=c++17 -pthread
if [ $? -ne 0 ]; then
    echo
    echo "Compilation failed. Exiting..."
    exit 1
fi

# Make the verification program executable
chmod +x verification

# Run the verification program
echo
echo "Running verification program..."
./verification
if [ $? -eq 0 ]; then
    echo
    echo "Verification completed successfully."
else
    echo
    echo "Verification failed. Exiting..."
    exit 1
fi

# Compile the shortest_path program
echo
echo "Compiling Quickest Path System..."
echo
g++ -std=c++17 -O3 -o shortest_path main.cpp graph.cpp preprocessing.cpp -pthread

# Run the shortest_path program

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