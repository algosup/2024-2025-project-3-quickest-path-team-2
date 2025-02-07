#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <cstdint>

/**
 * Represents an edge in the graph.
 */
struct Edge {
    int target;
    uint32_t weight;
    
    Edge(int target, uint32_t weight) : target(target), weight(weight) {}
};

/**
 * Graph class to represent a weighted undirected graph.
 */
class Graph {
public:
    Graph();
    void add_edge(int source, int target, int weight);
    std::vector<int> shortest_path(int source, int target, uint32_t& totalTime);
    int get_max_node_id() const;
    int get_travel_time(int landmark_1, int landmark_2) const;

private:
    std::vector<std::vector<Edge>> adjList; // Stockage direct des Edge au lieu de std::pair<int, int>
};

#endif // GRAPH_HPP
