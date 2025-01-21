#include "includes/graph.hpp"
#include <queue>
#include <stdexcept>
#include <algorithm>

// Ajout d'une arête entre deux nœuds
void Graph::add_edge(int source, int target, int weight) {
    adjList[source].push_back({target, weight});
    adjList[target].push_back({source, weight});
}

// Vérifier si un nœud existe
bool Graph::node_exists(int node) const {
    return adjList.find(node) != adjList.end();
}

// Recherche du chemin le plus court entre deux nœuds avec Dijkstra
std::vector<int> Graph::shortest_path(int source, int target, int& totalTime) {
    const int INF = std::numeric_limits<int>::max();

    if (!node_exists(source) || !node_exists(target)) {
        throw std::out_of_range("Source or target node does not exist in the graph.");
    }

    std::unordered_map<int, int> dist;       // Distance minimale depuis la source
    std::unordered_map<int, int> previous;   // Pour reconstruire le chemin
    std::unordered_map<int, bool> processed;  // Tableau pour marquer les nœuds traités
    dist[source] = 0;

    // File de priorité pour l'algorithme de Dijkstra
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int current = minHeap.top().second;
        int currentDist = minHeap.top().first;
        minHeap.pop();

        if (processed[current]) continue;
        processed[current] = true;

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

            if (newDist < dist[neighbor] || dist.find(neighbor) == dist.end()) {
                dist[neighbor] = newDist;
                previous[neighbor] = current;
                minHeap.push({newDist, neighbor});
            }
        }
    }

    totalTime = 0;
    return {}; // Aucun chemin trouvé
}
