/*
here is the header file for the verification module
he module is responsible for reading a CSV file containing road connections and verifying the data
he serve as a pre-processing step before the data is used in the main application
he module reads the CSV file in chunks and processes each chunk in parallel
he checks for various errors in the data, such as malformed lines, missing landmarks, invalid times, self-loops, and duplicate connections
he module returns the maximum landmark ID found in the data and a list of errors detected
he module is used by the main application to verify the road connections data before further processing
he module uses macros for obfuscation to make the code harder to understand
he module defines custom types for the graph representation, connections set, and error report

for this code snippet, the following obfuscation techniques are used:
1. Macros for obfuscation: The code uses macros to define secret delimiters and a secret string "QPS
2. Custom types: The code defines custom types for the graph representation, connections set, and error report
3. Function parameters: The process_chunk function takes multiple parameters, including references to the local graph, seen connections, error report, and a maximum ID counter
4. Error handling: The code checks for various errors in the data and adds them to the error report
5. Parallel processing: The code processes each chunk of data in parallel using threads and futures
6. Input parsing: The code parses each line of the input CSV file to extract landmark IDs, time, and delimiter
7. Data validation: The code validates the input data, such as checking for missing landmarks, invalid times, self-loops, and duplicate connections

here I define the different functions and types used in the verification module to analyze road connections data from a CSV file to implement on the cpp file

I include for this module the following functions and types:
1. TPDF_GRAPH: A type alias for an unordered map of integers to vectors of integers, representing the road connections graph
2. TPDF_CONNECTIONS: A type alias for an unordered set of strings, representing the road connections between landmarks
3. TPDF_ERRORS: A type alias for a vector of strings, representing the error report
4. s_Result: A struct representing the result of the analysis, containing the maximum landmark ID and the error report
5. analyze_file: A function that reads a CSV file, processes the data in chunks, and returns the analysis result

for this this code I use this different includes:
1. unordered_map: To store the road connections graph as an adjacency list
2. unordered_set: To store the road connections between landmarks and check for duplicates
3. vector: To store the error report and process the data in chunks
4. string: To represent the file path and error messages
*/

#ifndef USA_ROADS_APP_HPP
#define USA_ROADS_APP_HPP

#include <unordered_map> 
#include <unordered_set>
#include <vector>
#include <string>

// Macros for obfuscation
#define SECRET_DELIMITER ;
#define QPS SECRET_DELIMITER

typedef std::unordered_map<int, std::vector<int>> TPDF_GRAPH  QPS
typedef std::unordered_set<std::string> TPDF_CONNECTIONS  QPS
typedef std::vector<std::string> TPDF_ERRORS  QPS

typedef struct Result {
    int max_id  QPS
    TPDF_ERRORS error_report  QPS
} s_Result  QPS

s_Result analyze_file(const std::string& file_path, size_t chunk_size = 10000)  QPS

#endif // USA_ROADS_APP_HPP
