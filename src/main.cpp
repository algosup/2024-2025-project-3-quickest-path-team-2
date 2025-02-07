#include "includes/graph.hpp"
#include "includes/preprocessing.hpp"
#include "api/api.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <thread>
#include <chrono>

// Fonction pour afficher le logo
// void display_logo(const std::string& file_path) {
//     std::ifstream logo_file(file_path);
//     if (logo_file.is_open()) {
//         std::string line;
//         while (getline(logo_file, line)) {
//             std::cout << line << std::endl;
//         }
//         logo_file.close();
//     } else {
//         std::cerr << "Erreur : Impossible d'ouvrir le fichier logo." << std::endl;
//     }
// }

int main(int argc, char* argv[]) {
    // std::string logoFilePath = "logo/logo_qps.txt";  
    // display_logo(logoFilePath);

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::string inputFilePath = argv[1];
    Graph graph;

    try {
        // Lancer le preprocessing
        auto preprocessingStart = std::chrono::high_resolution_clock::now();
        preprocess_data(inputFilePath, 0, graph);
        auto preprocessingEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> preprocessingTime = preprocessingEnd - preprocessingStart;

        std::cout << "Preprocess finished. Data loaded in memory.\n";
        std::cout << "Preprocess time: " << preprocessingTime.count() << " seconds.\n";

        // Lancer l'API dans un thread séparé
        std::thread apiThread(start_api, std::ref(graph));

        // Attendre que l'API se termine
        apiThread.join();

    } catch (const std::exception& e) {
        std::cerr << "Error : " << e.what() << "\n";
        return 1;
    }

    return 0;
}
