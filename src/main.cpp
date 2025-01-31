#include "includes/graph.hpp"
#include "includes/preprocessing.hpp"
#include <iostream>
#include <chrono>
#include <iomanip> // For std::setprecision

/**
 * Main function to preprocess data and find the shortest path in the graph.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 on success, 1 on error.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::string inputFilePath = argv[1];
    Graph graph;

    try {
        int maxLines = 28854314; // Total number of lines to process
        std::cout << "Starting preprocessing..." << std::endl;

        auto startPreprocess = std::chrono::steady_clock::now();
        preprocess_data(inputFilePath, maxLines, graph);
        auto endPreprocess = std::chrono::steady_clock::now();

        auto preprocessDuration = std::chrono::duration_cast<std::chrono::seconds>(endPreprocess - startPreprocess);
        std::cout << "\nPreprocessing completed in " << preprocessDuration.count() << " seconds." << std::endl;

        // Verify the graph
        int maxNode = graph.get_max_node_id();
        std::cout << "Graph loaded with max node ID: " << maxNode << std::endl;

        // Prompt user for source and target nodes
        int source, target;
        std::cout << "Enter the source node: ";
        std::cin >> source;
        std::cout << "Enter the target node: ";
        std::cin >> target;

        // Validate the nodes
        if (source < 0 || source > maxNode || target < 0 || target > maxNode) {
            std::cerr << "Error: Source or target node is out of bounds." << std::endl;
            return 1;
        }

        std::cout << "Finding shortest path from " << source << " to " << target << "..." << std::endl;

        // Calculate the shortest path
        long long totalTime = 0;  // Use long long for total time
        auto startPath = std::chrono::steady_clock::now();
        std::vector<int> path = graph.shortest_path(source, target, totalTime);
        auto endPath = std::chrono::steady_clock::now();

        auto pathDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endPath - startPath);

        // Display the results
        if (path.empty()) {
            std::cout << "No path found between " << source << " and " << target << "." << std::endl;
        } else {
            std::cout << "Shortest path found with total time " << totalTime << ":\n";
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i];
                if (i != path.size() - 1) std::cout << " -> ";
            }
            std::cout << std::endl;
        }

        std::cout << "Path calculation took " << pathDuration.count() << " ms." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}