#include "includes/graph.hpp"
#include "includes/preprocessing.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <chrono> // To measure the execution time


// Function to display the logo
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
        // Measure the preprocessing time
        auto preprocessingStart = std::chrono::high_resolution_clock::now();
        preprocess_data(inputFilePath, 0, graph);
        auto preprocessingEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> preprocessingTime = preprocessingEnd - preprocessingStart;

        std::cout << "Preprocessing completed. Data loaded into memory.\n";
        std::cout << "Time for preprocessing: " << preprocessingTime.count() << " seconds.\n";

        // Measure the time to calculate the shortest path
        auto pathCalculationStart = std::chrono::high_resolution_clock::now();
        int totalTime;
        std::vector<int> path = graph.shortest_path(source, target, totalTime);
        auto pathCalculationEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> pathCalculationTime = pathCalculationEnd - pathCalculationStart;

        if (path.empty()) {
            std::cout << "No path founded between " << source << " and " << target << ".\n";
        } else {
            std::cout << "Shortest path: ";
            for (int node : path) {
                std::cout << node << " ";
            }
            std::cout << "\nTotal Time: " << totalTime << "\n";
        }

        std::cout << "Path calculation time: " << pathCalculationTime.count() << " seconds.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
