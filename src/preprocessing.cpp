#include "includes/preprocessing.hpp"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <unordered_map>

#define SECRET_DELIMITER ","

using TPDF_CONNECTIONS = std::unordered_map<int, std::unordered_set<int>>;

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
            continue;
        }

        if (landmarkA <= 0 || landmarkB <= 0 || time <= 0 || landmarkA == landmarkB) {
            continue;
        }

        if (seenConnections[landmarkA].count(landmarkB) > 0 || seenConnections[landmarkB].count(landmarkA) > 0) {
            continue;
        }

        graph.add_edge(landmarkA, landmarkB, time);
        seenConnections[landmarkA].insert(landmarkB);
        seenConnections[landmarkB].insert(landmarkA);

        maxId.store(std::max(maxId.load(), std::max(landmarkA, landmarkB)));
    }
}

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
