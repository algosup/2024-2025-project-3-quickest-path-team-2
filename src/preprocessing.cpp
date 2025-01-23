#include "includes/preprocessing.hpp"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <unordered_map>

#define SECRET_DELIMITER ","

// Alias for connections
using TPDF_CONNECTIONS = std::unordered_map<int, std::unordered_set<int>>;

// Data processing to populate the graph
void process_chunk(
    std::ifstream& inputFile,
    Graph& graph,
    TPDF_CONNECTIONS& seenConnections,
    std::atomic<int>& maxId,
    int maxLines
) {
    std::string line;
    int lineCount = 0;

    while (std::getline(inputFile, line) && (maxLines <= 0 || lineCount < maxLines)) {
        lineCount++;

        std::istringstream ss(line);
        int landmarkA, landmarkB, time;
        char delimiter;

        if (!(ss >> landmarkA >> delimiter >> landmarkB >> delimiter >> time) || delimiter != ',') {
            continue; // Ignore the invalid lines
        }

        if (landmarkA <= 0 || landmarkB <= 0 || time <= 0 || landmarkA == landmarkB) {
            continue; // Ignore invalid connections or loops
        }

        if (seenConnections[landmarkA].count(landmarkB) > 0 || seenConnections[landmarkB].count(landmarkA) > 0) {
            continue; // Ignore duplicate connections
        }

        // Add to the graph
        graph.add_edge(landmarkA, landmarkB, time);

        // Mark connections as seen
        seenConnections[landmarkA].insert(landmarkB);
        seenConnections[landmarkB].insert(landmarkA);

        // Update maxId
        maxId.store(std::max(maxId.load(), std::max(landmarkA, landmarkB)));
    }
}

// Preprocess the data to store them in a graph
bool preprocess_data(const std::string& filePath, int maxLines, Graph& graph) {
    TPDF_CONNECTIONS seenConnections;
    std::atomic<int> maxId(0);

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Impossible to open the CSV file: " + filePath);
    }

    process_chunk(inputFile, graph, seenConnections, maxId, maxLines);

    inputFile.close();
    return true;
}