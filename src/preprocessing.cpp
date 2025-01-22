#include "includes/preprocessing.hpp"
#include "includes/graph.hpp"
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>

#define SECRET_DELIMITER ","

using namespace std;

// Alias types for graph and connections
using TPDF_GRAPH = unordered_map<int, vector<int>>;
using TPDF_CONNECTIONS = unordered_set<string>;
using TPDF_CONNECTIONS_WITH_TIME = vector<s_Connection>;

// Generate JSON file manually (if needed)
void write_json_to_file(const TPDF_CONNECTIONS_WITH_TIME& connectionsWithTime, const string& outputJsonFile) {
    if (outputJsonFile.empty()) {
        return; // Skip writing if no file path is specified
    }

    ofstream jsonFile(outputJsonFile);
    if (!jsonFile.is_open()) {
        throw runtime_error("Error: Unable to open output file " + outputJsonFile);
    }

    jsonFile << "{\n  \"connections\": [\n";
    for (size_t i = 0; i < connectionsWithTime.size(); ++i) {
        const auto& conn = connectionsWithTime[i];
        jsonFile << "    {\n"
                 << "      \"ID1\": " << conn.landmarkA << ",\n"
                 << "      \"ID2\": " << conn.landmarkB << ",\n"
                 << "      \"weight\": " << conn.time << "\n"
                 << "    }";
        if (i < connectionsWithTime.size() - 1) {
            jsonFile << ",";
        }
        jsonFile << "\n";
    }
    jsonFile << "  ]\n}\n";
}

// Process a chunk of lines to populate the graph and store connections with time
void process_chunk(
    ifstream& inputFile, // pass the file stream directly for more efficient reading
    Graph& graph,
    TPDF_CONNECTIONS& seenConnections,
    std::atomic<int>& maxId,  // Utilisez std::atomic
    TPDF_CONNECTIONS_WITH_TIME& connectionsWithTime,
    int maxLines // Limit number of lines processed
) {
    string line;
    int lineCount = 0;

    while (getline(inputFile, line) && (maxLines <= 0 || lineCount < maxLines)) {
        lineCount++;

        std::istringstream ss(line);
        int landmarkA, landmarkB, time;
        char delimiter;

        // Extract data (landmarkA, landmarkB, time)
        if (!(ss >> landmarkA >> delimiter >> landmarkB >> delimiter >> time) || delimiter != ',') {
            continue; // Skip invalid lines
        }

        if (landmarkA <= 0 || landmarkB <= 0 || time <= 0 || landmarkA == landmarkB) {
            continue; // Skip invalid or self-loop connections
        }

        std::string connection = std::to_string(landmarkA) + SECRET_DELIMITER + std::to_string(landmarkB);
        std::string reverseConnection = std::to_string(landmarkB) + SECRET_DELIMITER + std::to_string(landmarkA);

        if (seenConnections.count(connection) > 0 || seenConnections.count(reverseConnection) > 0) {
            continue; // Skip duplicate connections
        }

        // Store connection with time in the vector
        s_Connection conn = {landmarkA, landmarkB, time};
        connectionsWithTime.push_back(conn);

        // Add the connection to the weighted graph
        graph.add_edge(landmarkA, landmarkB, time);

        // Add to the seen connections set
        seenConnections.insert(connection);
        seenConnections.insert(reverseConnection);

        // Update maxId
        maxId.store(std::max(maxId.load(), std::max(landmarkA, landmarkB)));
    }
}

// Preprocess the road connections data by storing it in a graph and loading connections with time
bool preprocess_data(const string& filePath, int maxLines, const string& outputJsonFile, Graph& graph) {
    TPDF_CONNECTIONS seenConnections;
    atomic<int> maxId(0);
    TPDF_CONNECTIONS_WITH_TIME connectionsWithTime;

    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        throw runtime_error("Error: Unable to find the CSV file!" + filePath);
    }

    // Process data in chunks directly from the file stream to avoid large memory usage
    process_chunk(inputFile, graph, seenConnections, maxId, connectionsWithTime, maxLines);

    // Generate the JSON file if a path is provided
    write_json_to_file(connectionsWithTime, outputJsonFile);

    inputFile.close();
    return true;
}
