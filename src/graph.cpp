#include "includes/graph.hpp"
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <iostream>

void Graph::add_edge(int source, int target, int weight) {
    if (source >= static_cast<int>(adjList.size()) || target >= static_cast<int>(adjList.size())) {
        adjList.resize(std::max(source, target) + 1);
    }
    adjList[source].emplace_back(target, weight);
    adjList[target].emplace_back(source, weight);
}

std::vector<int> Graph::shortest_path(int source, int target, int& totalTime) {
    constexpr int INF = std::numeric_limits<int>::max();

    if (source >= static_cast<int>(adjList.size()) || target >= static_cast<int>(adjList.size())) {
        throw std::out_of_range("Source or target node is out of bounds.");
    }

    size_t n = adjList.size();
    std::vector<int> dist(n, INF);
    std::vector<int> previous(n, -1);
    dist[source] = 0;

    using NodeDistPair = std::pair<int, int>;
    std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<>> minHeap;
    minHeap.emplace(0, source);

    while (!minHeap.empty()) {
        auto [currentDist, current] = minHeap.top();
        minHeap.pop();

        // Si la distance extraite est déjà supérieure, on passe
        if (currentDist > dist[current]) continue;

        // Si la cible est atteinte, on reconstruit directement le chemin
        if (current == target) {
            totalTime = dist[current];
            std::vector<int> path;
            for (int node = target; node != -1; node = previous[node]) {
                path.push_back(node);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const Edge& edge : adjList[current]) {
            int neighbor = edge.target;
            int newDist = currentDist + edge.weight;

            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                previous[neighbor] = current;
                minHeap.emplace(newDist, neighbor);
            }
        }
    }

    totalTime = 0;
    return {}; // Aucun chemin trouvé
}
