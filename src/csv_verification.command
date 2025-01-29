#!/bin/bash

# Navigate to the src directory
cd "$(dirname "$0")"

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