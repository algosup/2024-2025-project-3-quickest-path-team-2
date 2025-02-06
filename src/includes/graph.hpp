#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    int target;
    int weight;

    Edge(int target, int weight) : target(target), weight(weight) {}
};

class Graph {
public:
    Graph(); 

    void add_edge(int source, int target, int weight);
    std::vector<int> shortest_path(int source, int target, int& totalTime);
    int get_travel_time(int landmark_1, int landmark_2) const;





private:
std::vector<std::vector<Edge>> adjList;
};

#endif // GRAPH_HPP

