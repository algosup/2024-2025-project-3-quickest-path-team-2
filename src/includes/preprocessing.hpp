#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include "graph.hpp"
#include <atomic> // For atomic integer
#include <unordered_map> 
#include <unordered_set> 
#include <string>
#include <vector>
#include <thread>
#include <mutex> 
#include <iostream>
#include <fcntl.h> // For file control options to open files
#include <sys/mman.h> // For mmap and munmap functions to map files to memory
#include <unistd.h> // For close function to close file descriptors

using TPDF_CONNECTIONS = std::unordered_map<int, std::unordered_set<int>>; // Type alias for seen connections

// Process a chunk of the file to extract and store graph edges
void process_chunk(
    const char* fileData, // Pointer to the start of the file data in memory
    size_t fileSize, // Size of the file data
    Graph& graph, // Reference to the Graph object where edges will be added
    TPDF_CONNECTIONS& seenConnections, // Map to track already processed connections
    std::atomic<int>& maxId,// Atomic integer to keep track of the maximum node ID
    int maxLines,// Maximum number of lines to process (if <= 0, process all lines)
    std::mutex& mutex// Mutex for synchronization
);

bool preprocess_data(const std::string& filePath, int maxLines, Graph& graph); // Preprocess the data from the input file

#endif // PREPROCESSING_HPP