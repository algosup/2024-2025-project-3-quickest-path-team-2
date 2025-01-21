#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <limits>
#include <utility>

struct Edge {
    int target;  // Nœud cible de l'arête
    int weight;  // Poids de l'arête
};

class Graph {
public:
    // Ajouter une arête entre deux nœuds
    void add_edge(int source, int target, int weight);

    // Trouver le chemin le plus court entre deux nœuds
    std::vector<int> shortest_path(int source, int target, int& totalTime);

    // Vérifier si un nœud existe
    bool node_exists(int node) const;

private:
    std::unordered_map<int, std::vector<Edge>> adjList;  // Liste d'adjacence
};

#endif // GRAPH_HPP
