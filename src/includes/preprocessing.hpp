#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include "graph.hpp"
#include <atomic> // For atomic integer
#include <unordered_map> 
#include <unordered_set> 
#include <atomic> // For atomic integer
#include <unordered_map> 
#include <unordered_set> 
#include <string>
#include <vector>
#include <thread>
#include <mutex> 
#include <iostream>
#include <fcntl.h> // For file control options to open files
#ifdef _WIN32
#include <windows.h> // For VirtualAlloc and VirtualFree functions
#else
#include <sys/mman.h> // For mmap and munmap functions to map files to memory
#include <unistd.h> // For close function to close file descriptors
#endif
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

using TPDF_CONNECTIONS = std::unordered_map<int, std::unordered_set<int>>; // Type alias for seen connections

// Process a chunk of the file to extract and store graph edges
void process_chunk(
    const char* fileData, // Pointer to the start of the file data in memory
    size_t fileSize, // Size of the file data
    Graph& graph, // Reference to the Graph object where edges will be added
    TPDF_CONNECTIONS& seenConnections, // Map to track already processed connections
    std::atomic<int>& maxId,// Atomic integer to keep track of the maximum node ID
    int max_lines,// Maximum number of lines to process (if <= 0, process all lines)
    std::mutex& mutex// Mutex for synchronization
);

/**
 * Preprocesses the data from the input file and builds the graph.
 * 
 */
bool preprocess_data(const std::string& filePath, int max_lines, Graph& graph); // Preprocess the data from the input file

/**
 * Function to get the maximum number of lines in the .csv files in the data folder
 * @param dataFolderPath fs::path
 * @return int
 */
int get_max_lines(const fs::path& dataFolderPath);



#endif // PREPROCESSING_HPP