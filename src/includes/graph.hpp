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

private:
    std::vector<std::vector<std::pair<int, int>>> adjList; // Adjacency list representation of the graph
};

#endif // GRAPH_HPP