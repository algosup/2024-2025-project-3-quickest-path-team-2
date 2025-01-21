#include "includes/graph.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <stdexcept>

using namespace std;
using namespace chrono;

// Fonction pour afficher une barre de progression
void display_progress_bar(size_t current, size_t total) {
    const int barWidth = 50;
    float progress = static_cast<float>(current) / total;
    int position = static_cast<int>(progress * barWidth);

    cout << "\r[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < position) cout << "=";
        else if (i == position) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << "% (" << current << "/" << total << ")";
    cout.flush();
}

// Prétraitement des données
bool preprocess_data_with_progress(const string& filePath, int maxLines, Graph& graph, size_t& totalLinesProcessed) {
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        throw runtime_error("Error: Unable to open file " + filePath);
    }

    // Compter les lignes dans le fichier
    size_t totalLines = 0;
    string line;
    while (getline(inputFile, line)) {
        ++totalLines;
        if (maxLines > 0 && totalLines >= static_cast<size_t>(maxLines)) break;
    }
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    // Charger les données dans le graphe
    size_t currentLine = 0;
    while (getline(inputFile, line) && (maxLines <= 0 || currentLine < static_cast<size_t>(maxLines))) {
        ++currentLine;

        int source, target, weight;
        if (sscanf(line.c_str(), "%d,%d,%d", &source, &target, &weight) == 3) {
            graph.add_edge(source, target, weight);
        }

        display_progress_bar(currentLine, totalLines);
    }

    inputFile.close();
    cout << endl;

    totalLinesProcessed = currentLine;
    return true;
}

int main() {
    string inputFilePath = "data/usa_roads.csv";  // Remplacez par le chemin de votre fichier CSV
    int maxLines = 28854314;  // Nombre maximal de lignes à traiter (ou -1 pour tout charger)

    Graph graph;

    size_t totalLinesProcessed = 0;
    try {
        cout << "Prétraitement des données en cours..." << endl;
        auto startTime = high_resolution_clock::now();

        preprocess_data_with_progress(inputFilePath, maxLines, graph, totalLinesProcessed);

        auto endTime = high_resolution_clock::now();
        duration<double> elapsed = endTime - startTime;

        cout << "Prétraitement terminé avec succès !" << endl;
        cout << "Nombre total de lignes traitées : " << totalLinesProcessed << endl;
        cout << "Temps écoulé : " << elapsed.count() << " secondes." << endl;
    } catch (const exception& e) {
        cerr << "Erreur: " << e.what() << endl;
        return 1;
    }

    // Boucle principale pour entrer les requêtes de chemin le plus court
    while (true) {
        int source, target;
        cout << "Entrez le point de départ (ou -1 pour quitter) : ";
        cin >> source;
        if (source == -1) break;

        cout << "Entrez le point d'arrivée : ";
        cin >> target;

        cout << "Recherche du chemin le plus court..." << endl;
        auto startTime = high_resolution_clock::now();

        int totalTime = 0;
        auto path = graph.shortest_path(source, target, totalTime);

        auto endTime = high_resolution_clock::now();
        duration<double> elapsed = endTime - startTime;

        if (path.empty()) {
            cout << "Aucun chemin trouvé entre " << source << " et " << target << "." << endl;
        } else {
            cout << "Chemin le plus court de " << source << " à " << target << " : ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << "\nTemps total : " << totalTime << " unités." << endl;
            cout << "Recherche terminée en " << elapsed.count() << " secondes." << endl;
        }
    }

    cout << "Programme terminé. Merci d'avoir utilisé notre service !" << endl;
    return 0;
}
