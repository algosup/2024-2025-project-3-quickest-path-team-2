#include "includes/graph.hpp"
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <iostream>

// Constructeur par défaut
Graph::Graph() : adjList() {}

// Ajouter une arête au graphe
void Graph::add_edge(int source, int target, int weight) {
    if (source >= static_cast<int>(adjList.size()) || target >= static_cast<int>(adjList.size())) {
        adjList.resize(std::max(source, target) + 1);
    }
    adjList[source].emplace_back(target, weight);
    adjList[target].emplace_back(source, weight);
}

// Trouver le chemin le plus court entre deux nœuds avec une optimisation bidirectionnelle
std::vector<int> Graph::shortest_path(int source, int target, int& totalTime) {
    constexpr int INF = std::numeric_limits<int>::max();

    if (source < 0 || source >= static_cast<int>(adjList.size()) ||
        target < 0 || target >= static_cast<int>(adjList.size())) {
        throw std::out_of_range("Source or target node is out of bounds.");
    }

    size_t n = adjList.size();
    std::vector<int> distForward(n, INF), distBackward(n, INF);
    std::vector<int> prevForward(n, -1), prevBackward(n, -1);
    std::vector<bool> processedForward(n, false), processedBackward(n, false);

    distForward[source] = 0;
    distBackward[target] = 0;

    using NodeDistPair = std::pair<int, int>;
    auto comparator = [](const NodeDistPair& a, const NodeDistPair& b) {
        return a.first > b.first;
    };

    std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, decltype(comparator)>
        pqForward(comparator), pqBackward(comparator);

    pqForward.emplace(0, source);
    pqBackward.emplace(0, target);

    int bestCost = INF;
    int meetingNode = -1;

    // Processus bidirectionnel
    while (!pqForward.empty() || !pqBackward.empty()) {
        // Expansion dans la direction avant
        if (!pqForward.empty()) {
            auto [currentDistF, currentNodeF] = pqForward.top();
            pqForward.pop();

            if (processedForward[currentNodeF]) continue;
            processedForward[currentNodeF] = true;

            for (const Edge& edge : adjList[currentNodeF]) {
                int neighbor = edge.target;
                int newDist = distForward[currentNodeF] + edge.weight;

                if (newDist < distForward[neighbor]) {
                    distForward[neighbor] = newDist;
                    prevForward[neighbor] = currentNodeF;

                    if (!processedForward[neighbor]) {
                        pqForward.emplace(newDist, neighbor);
                    }
                }

                if (processedBackward[neighbor]) {
                    int potentialCost = distForward[neighbor] + distBackward[neighbor];
                    if (potentialCost < bestCost) {
                        bestCost = potentialCost;
                        meetingNode = neighbor;
                    }
                }
            }
        }

        // Expansion dans la direction arrière
        if (!pqBackward.empty()) {
            auto [currentDistB, currentNodeB] = pqBackward.top();
            pqBackward.pop();

            if (processedBackward[currentNodeB]) continue;
            processedBackward[currentNodeB] = true;

            for (const Edge& edge : adjList[currentNodeB]) {
                int neighbor = edge.target;
                int newDist = distBackward[currentNodeB] + edge.weight;

                if (newDist < distBackward[neighbor]) {
                    distBackward[neighbor] = newDist;
                    prevBackward[neighbor] = currentNodeB;

                    if (!processedBackward[neighbor]) {
                        pqBackward.emplace(newDist, neighbor);
                    }
                }

                if (processedForward[neighbor]) {
                    int potentialCost = distForward[neighbor] + distBackward[neighbor];
                    if (potentialCost < bestCost) {
                        bestCost = potentialCost;
                        meetingNode = neighbor;
                    }
                }
            }
        }

        // Sortie anticipée si on a trouvé un chemin
        if (meetingNode != -1) break;
    }

    if (meetingNode == -1) {
        totalTime = 0;
        return {};
    }

    totalTime = bestCost;

    // Reconstruction du chemin
    std::vector<int> path;
    path.reserve(n); // Réserver la capacité maximale possible pour éviter les réallocations

    // Construire le chemin avant et l'ajouter directement au chemin final
    int forwardPathSize = 0;
    for (int node = meetingNode; node != -1; node = prevForward[node]) {
        path.push_back(node);
        forwardPathSize++;
    }

    // Inverser la partie avant du chemin pour obtenir le chemin complet
    std::reverse(path.begin(), path.begin() + forwardPathSize);

    // Construire le chemin arrière et l'ajouter directement au chemin final
    for (int node = prevBackward[meetingNode]; node != -1; node = prevBackward[node]) {
        path.push_back(node);
    }

    return path;
}