#include "includes/graph.hpp"
#include "includes/preprocessing.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <chrono> // To measure the execution time

void display_logo(const std::string& file_path) {
    std::ifstream logo_file(file_path);
    if (logo_file.is_open()) {
        std::string line;
        while (getline(logo_file, line)) {
            std::cout << line << std::endl;
        }
        logo_file.close();
    } else {
        std::cerr << "Error: Unable to open logo file." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string logoFilePath = "logo/logo_qps.txt";  // File path containing the logo
    display_logo(logoFilePath);
    
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <source> <target>\n";
        return 1;
    }

    std::string inputFilePath = argv[1];
    int source = std::stoi(argv[2]);
    int target = std::stoi(argv[3]);

    Graph graph;

    try {
        int maxLines = 28854314;
        preprocess_data(inputFilePath, maxLines, graph);

        // Check if source and target are within bounds
        if (source < 0 || source > graph.get_max_node_id() || target < 0 || target > graph.get_max_node_id()) {
            std::cerr << "Error: Source or target node is out of bounds. Source: " 
                      << source << ", Target: " << target << std::endl;
            return 1;
        }

        int totalTime = 0;
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> path = graph.shortest_path(source, target, totalTime);
        auto end = std::chrono::high_resolution_clock::now();

        if (path.empty()) {
            std::cout << "No path found between " << source << " and " << target << std::endl;
        } else {
            std::cout << "Shortest path found with total time " << totalTime << ":\n";
            for (int node : path) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " ms" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}