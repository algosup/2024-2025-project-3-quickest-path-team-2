#pragma once
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "graph.hpp"

typedef struct s_Connection {
    int landmarkA;
    int landmarkB;
    int time;
} s_Connection;

typedef struct s_Result {
    int maxId;
    std::vector<std::string> errorReport;
} s_Result;

typedef std::unordered_map<int, std::vector<int>> TPDF_GRAPH;
typedef std::unordered_set<std::string> TPDF_CONNECTIONS;
typedef std::vector<s_Connection> TPDF_CONNECTIONS_WITH_TIME; // 

s_Result analyze_file(const std::string& filePath, int maxLines);

bool preprocess_data(const std::string& filePath, int maxLines);

//json file
void write_json_to_file(const TPDF_CONNECTIONS_WITH_TIME& connectionsWithTime, const std::string& outputJsonFile);

bool preprocess_data(const std::string& filePath, int maxLines, const std::string& outputJsonFile);

void process_chunk(
    const std::vector<std::string>& lines,  // Remarque : Utilisez std::string et std::vector
    Graph& graph,
    TPDF_CONNECTIONS& seenConnections,
    std::atomic<int>& maxId,  // Remarque : Utilisez std::atomic
    TPDF_CONNECTIONS_WITH_TIME& connectionsWithTime
);
