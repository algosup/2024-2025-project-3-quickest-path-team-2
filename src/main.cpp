#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <string>
#include "includes/graph.hpp"
#include "includes/utils.hpp"

bool preprocess_data_with_progress(const std::string& filePath, int maxLines, Graph& graph, size_t& totalLinesProcessed) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filePath);
    }

    std::string line;
    size_t totalLines = 0;
    while (std::getline(inputFile, line)) {
        ++totalLines;
        if (maxLines > 0 && totalLines >= static_cast<size_t>(maxLines)) break;
    }

    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    size_t currentLine = 0;
    while (std::getline(inputFile, line) && (maxLines <= 0 || currentLine < static_cast<size_t>(maxLines))) {
        ++currentLine;

        int source, target, weight;
        if (sscanf(line.c_str(), "%d,%d,%d", &source, &target, &weight) == 3) {
            graph.add_edge(source, target, weight);
        }

        display_progress_bar(currentLine, totalLines);
    }

    inputFile.close();
    std::cout << std::endl;

    totalLinesProcessed = currentLine;
    return true;
}

int main() {
    std::string inputFilePath = "data/usa_roads.csv";  // Remplacez par le chemin de votre fichier CSV
    int maxLines = 28854314;  // Nombre maximal de lignes à traiter (ou -1 pour tout charger)

    Graph graph;
    size_t totalLinesProcessed = 0;

    try {
        std::cout << "Prétraitement des données en cours..." << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();

        preprocess_data_with_progress(inputFilePath, maxLines, graph, totalLinesProcessed);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = endTime - startTime;

        std::cout << "Prétraitement terminé avec succès !" << std::endl;
        std::cout << "Nombre total de lignes traitées : " << totalLinesProcessed << std::endl;
        std::cout << "Temps écoulé : " << elapsed.count() << " secondes." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    while (true) {
        int source, target;
        std::cout << "Entrez le point de départ (ou -1 pour quitter) : ";
        std::cin >> source;
        if (source == -1) break;

        std::cout << "Entrez le point d'arrivée : ";
        std::cin >> target;

        std::cout << "Recherche du chemin le plus court..." << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();

        int totalTime = 0;
        try {
            auto path = graph.shortest_path(source, target, totalTime);

            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = endTime - startTime;

            if (path.empty()) {
                std::cout << "Aucun chemin trouvé entre " << source << " et " << target << "." << std::endl;
            } else {
                std::cout << "Chemin le plus court de " << source << " à " << target << " : ";
                for (int node : path) {
                    std::cout << node << " ";
                }
                std::cout << "\nTemps total : " << totalTime << " unités." << std::endl;
                std::cout << "Recherche terminée en " << elapsed.count() << " secondes." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors de la recherche du chemin : " << e.what() << std::endl;
        }
    }

    std::cout << "Programme terminé. Merci d'avoir utilisé notre service !" << std::endl;
    return 0;
}
