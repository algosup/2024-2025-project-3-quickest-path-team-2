#!/bin/bash

# Navigate to the src directory
cd "$(dirname "$0")/src"

# Print the current directory for debugging
echo "Current directory: $(pwd)"

# Install necessary packages
echo
echo "Installing necessary packages..."
echo
brew install cmake asio boost
if [ $? -ne 0 ]; then
    echo
    echo "Package installation failed. Exiting..."
    echo
    exit 1
fi

# Compile the verification program
echo
echo "Compiling verification program..."
echo
g++ -o verification main_verification.cpp verification.cpp -std=c++17 -pthread
if [ $? -ne 0 ]; then
    echo
    echo "Compilation failed. Exiting..."
    echo
    exit 1
fi

# Make the verification program executable
chmod +x verification

# Run the verification program
echo
echo "Running verification program..."
echo
./verification
if [ $? -eq 0 ]; then
    echo
    echo "Verification completed successfully."
    echo
else
    echo
    echo "Verification failed. Exiting..."
    echo
    exit 1
fi

# Run cmake and make
echo
echo "Running cmake and make..."
echo
cmake . && make
if [ $? -ne 0 ]; then
    echo
    echo "CMake or make failed. Exiting..."
    echo
    exit 1
fi

# Navigate to the build directory
cd build

# Check if CrowExample exists and is executable
if [ ! -x ./CrowExample ]; then
    echo
    echo "CrowExample not found or not executable. Exiting..."
    echo
    exit 1
fi

# Run the CrowExample program
echo
echo "Running CrowExample program..."
echo
./CrowExample &
sleep 2  # Give the server time to start
echo

# Launch the web page after a delay
echo
echo "Launching web page..."
sleep 2 && open "http://localhost:8080"
echo

echo
echo "Script completed successfully."
echo