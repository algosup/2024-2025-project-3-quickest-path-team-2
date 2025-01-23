#include "includes/graph.hpp"
#include "includes/preprocessing.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono> // Pour mesurer le temps d'exécution

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <source> <target>\n";
        return 1;
    }

    std::string inputFilePath = argv[1];
    int source = std::stoi(argv[2]);
    int target = std::stoi(argv[3]);

    Graph graph;

    try {
        // Mesurer le temps de prétraitement
        auto preprocessingStart = std::chrono::high_resolution_clock::now();
        preprocess_data(inputFilePath, 0, graph);
        auto preprocessingEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> preprocessingTime = preprocessingEnd - preprocessingStart;

        std::cout << "Prétraitement terminé. Données chargées en mémoire.\n";
        std::cout << "Temps de prétraitement : " << preprocessingTime.count() << " secondes.\n";

        // Mesurer le temps de calcul du chemin le plus court
        auto pathCalculationStart = std::chrono::high_resolution_clock::now();
        int totalTime;
        std::vector<int> path = graph.shortest_path(source, target, totalTime);
        auto pathCalculationEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> pathCalculationTime = pathCalculationEnd - pathCalculationStart;

        if (path.empty()) {
            std::cout << "Aucun chemin trouvé entre " << source << " et " << target << ".\n";
        } else {
            std::cout << "Chemin le plus court : ";
            for (int node : path) {
                std::cout << node << " ";
            }
            std::cout << "\nTemps total : " << totalTime << "\n";
        }

        std::cout << "Temps de calcul du chemin : " << pathCalculationTime.count() << " secondes.\n";

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
        return 1;
    }

    return 0;
}
