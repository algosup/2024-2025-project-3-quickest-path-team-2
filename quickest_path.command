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

# Navigate to the build directory
rm build
mkdir build
cd build

# Run cmake
echo
echo "Running cmake..."
echo
cmake ..
if [ $? -ne 0 ]; then
    echo
    echo "CMake failed. Exiting..."
    echo
    exit 1
fi

# Run make
echo
echo "Running make..."
echo
make 
if [ $? -ne 0 ]; then
    echo
    echo "Make failed. Exiting..."
    echo
    exit 1
fi

# Check if QPS exists and is executable
if [ ! -x ./QPS ]; then
    echo
    echo "QPS not found or not executable. Exiting..."
    echo
    exit 1
fi

# Run the CrowExample program
echo
echo "Running QPS program..."
echo
./QPS
sleep 2  # Give the server time to start
echo

# Launch the web page after a delay
echo
echo "Launching web page..."
sleep 2 && open "http://127.0.0.1:5501/src/api/static/"
echo

echo
echo "Script completed successfully."
echo