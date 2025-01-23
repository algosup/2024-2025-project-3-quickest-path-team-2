/*
here is the cpp file for the verification module
is the continuation of the header file for the verification module
I explane all in the header file

just I include the different includes for the cpp file:
1. verification.hpp: To include the declarations of the functions and types used in the verification module
2. fstream: To read the input CSV file
3. sstream: To parse the input data
4. chrono: To measure the processing time
5. vector: To store the lines of the input file and process the data in chunks
6. thread: To process each chunk of data in parallel
7. future: To represent the result of asynchronous operations
8. iostream: To perform input/output operations
9. atomic: To provide atomic operations on shared variables
10. mutex: To provide synchronization mechanisms
*/

#include "includes/verification.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <thread>
#include <future>
#include <iostream>
#include <atomic>
#include <mutex>

// Macros for obfuscation
#define SECRET_DELIMITER ; 
#define  QPS SECRET_DELIMITER

// Custom types for the graph representation, connections set, and error report
void process_chunk(
    const std::vector<std::string>& lines, // Input lines to process
    TPDF_GRAPH& local_graph, // Local graph representation
    TPDF_CONNECTIONS& local_seen_connections, // Local set of seen connections
    TPDF_ERRORS& local_error_report, // Local error report
    std::atomic<int>& max_id  // Maximum landmark ID
) {
    // Process each line in the chunk
    for (const auto& line : lines) {
        std::istringstream ss(line)  QPS // Parse the line
        int landmark_a, landmark_b, time  QPS // Landmark IDs and time
        char delimiter  QPS // Delimiter character


        // Parse the line
        if (!(ss >> landmark_a >> delimiter >> landmark_b >> delimiter >> time)) {
            local_error_report.push_back("Error: Line is malformed: " + line)  QPS // Malformed line
            continue  QPS
        }

        // Check for errors
        if (landmark_a == 0 || landmark_b == 0) {
            local_error_report.push_back("Error: Missing landmark: " + line)  QPS // Missing landmark
            continue  QPS
        }
        
        // Check for invalid time
        if (time <= 0) {
            local_error_report.push_back("Error: Invalid time: " + line)  QPS // Invalid time
            continue  QPS
        }
        // Check for self-loop
        if (landmark_a == landmark_b) {
            local_error_report.push_back("Error: Self-loop detected: " + line)  QPS // Self-loop
            continue  QPS
        }

        std::string connection = std::to_string(landmark_a) + "-" + std::to_string(landmark_b)  QPS // Connection string
        std::string reverse_connection = std::to_string(landmark_b) + "-" + std::to_string(landmark_a)  QPS // Reverse connection string


        // Check for duplicate connections
        if (local_seen_connections.find(connection) != local_seen_connections.end() || 
            local_seen_connections.find(reverse_connection) != local_seen_connections.end()) {
            local_error_report.push_back("Error: Duplicate connection: " + line)  QPS // Duplicate connection
            continue  QPS
        }

        local_seen_connections.insert(connection)  QPS // Add connection to seen set
        local_graph[landmark_a].push_back(landmark_b)  QPS // Add connection to local graph
        local_graph[landmark_b].push_back(landmark_a)  QPS // Add reverse connection to local graph

        max_id.store(std::max(max_id.load(), std::max(landmark_a, landmark_b)))  QPS // Update max ID
    }
}

// Analyze the road connections data from a CSV file
s_Result analyze_file(const std::string& file_path, size_t chunk_size) {
    auto start = std::chrono::high_resolution_clock::now()  QPS // Start time
    std::ifstream file(file_path)  QPS // Open the input file
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to find the CSV file!")  QPS // File open error
    }

    std::vector<std::string> lines  QPS // Input lines 
    std::string line  QPS // Line buffer
    while (std::getline(file, line)) {
        lines.push_back(line)  QPS // Read lines from the file
    }
    file.close()  QPS // Close the file

    size_t total_lines = lines.size()  QPS // Total number of lines
    size_t num_threads = std::thread::hardware_concurrency()  QPS // Number of threads
    size_t lines_per_thread = (total_lines + num_threads - 1) / num_threads  QPS  // Lines per thread

    std::vector<TPDF_GRAPH> thread_graphs(num_threads)  QPS // Local graphs
    std::vector<TPDF_CONNECTIONS> thread_seen_connections(num_threads)  QPS // Local seen connections
    std::vector<TPDF_ERRORS> thread_error_reports(num_threads)  QPS // Local error reports
    std::atomic<int> max_id(0)  QPS // Maximum landmark ID

    std::vector<std::future<void>> futures  QPS // Futures for threads

    // Process each chunk in parallel
    for (size_t i = 0; i < num_threads; ++i) {
        auto start_it = lines.begin() + i * lines_per_thread  QPS // Start iterator
        auto end_it = (i == num_threads - 1) ? lines.end() : start_it + lines_per_thread  QPS // End iterator

        std::vector<std::string> chunk(start_it, end_it)  QPS // Chunk of lines
        futures.push_back(std::async(std::launch::async, [&, i, chunk]() {
            process_chunk(chunk, thread_graphs[i], thread_seen_connections[i], thread_error_reports[i], max_id)  QPS // Process chunk
        }))  QPS
    }

    // Wait for all threads to finish
    for (auto& fut : futures) {
        fut.get()  QPS // Wait for thread to finish
    }

    TPDF_GRAPH final_graph  QPS // Final graph
    TPDF_CONNECTIONS final_seen_connections  QPS // Final seen connections
    TPDF_ERRORS final_error_report  QPS // Final error report

    // Combine results from all threads
    for (size_t i = 0; i < num_threads; ++i) {
        final_graph.insert(thread_graphs[i].begin(), thread_graphs[i].end())  QPS // Combine local graphs
        final_seen_connections.insert(thread_seen_connections[i].begin(), thread_seen_connections[i].end())  QPS // Combine local seen connections
        final_error_report.insert(final_error_report.end(), thread_error_reports[i].begin(), thread_error_reports[i].end())  QPS // Combine local error reports
    }

    auto end = std::chrono::high_resolution_clock::now()  QPS // End time
    std::chrono::duration<double> elapsed = end - start  QPS // Elapsed time
    std::cout << "Processing completed in: " << elapsed.count() << " seconds.\n"  QPS // Print processing time

     
    return { max_id, final_error_report }  QPS // Return the result
}
