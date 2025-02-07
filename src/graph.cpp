#include "includes/graph.hpp"
#include <stdexcept>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>

/**
 * Default constructor for the Graph class.
 */
Graph::Graph() {}

/**
 * Returns the travel time between two landmarks.
 */
int Graph::get_travel_time(int landmark_1, int landmark_2) const {
    if (landmark_1 < 0 || landmark_1 >= static_cast<int>(adjList.size()) ||
        landmark_2 < 0 || landmark_2 >= static_cast<int>(adjList.size())) {
        throw std::out_of_range("Landmark ID is out of bounds.");
    }

    for (const Edge& edge : adjList[landmark_1]) {
        if (edge.target == landmark_2) {
            return edge.weight;
        }
    }

    return -1;
}

/**
 * Adds an edge to the graph.
 */
void Graph::add_edge(int source, int target, int weight) {
    if (std::max(source, target) >= adjList.size()) {
        adjList.resize(std::max(source, target) + 1);
    }
    adjList[source].emplace_back(target, weight);
    adjList[target].emplace_back(source, weight);
}

/**
 * Returns the maximum node ID in the graph.
 */
int Graph::get_max_node_id() const {
    return adjList.size() - 1;
}

/**
 * Finds the shortest path using bidirectional Dijkstra's algorithm.
 */
std::vector<int> Graph::shortest_path(int source, int target, uint32_t& totalTime) {
    constexpr uint32_t INF = std::numeric_limits<uint32_t>::max();
    int maxNodeId = get_max_node_id();

    if (source >= adjList.size() || target >= adjList.size()) {
        throw std::out_of_range("Source or target node is out of bounds.");
    }

    std::vector<uint32_t> distForward(maxNodeId + 1, INF);
    std::vector<uint32_t> distBackward(maxNodeId + 1, INF);
    std::vector<int> prevForward(maxNodeId + 1, -1);
    std::vector<int> prevBackward(maxNodeId + 1, -1);
    std::vector<bool> processedForward(maxNodeId + 1, false);
    std::vector<bool> processedBackward(maxNodeId + 1, false);

    distForward[source] = 0;
    distBackward[target] = 0;

    using NodeDistPair = std::pair<uint32_t, int>;
    auto comparator = [](const NodeDistPair& a, const NodeDistPair& b) {
        return a.first > b.first;
    };

    std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, decltype(comparator)> pqForward(comparator), pqBackward(comparator);

    pqForward.emplace(0, source);
    pqBackward.emplace(0, target);

    uint32_t bestCost = INF;
    int meetingNode = -1;

    while (!pqForward.empty() && !pqBackward.empty()) {
        // Process forward search
        if (!pqForward.empty()) {
            auto [currentDist, currentNode] = pqForward.top();
            pqForward.pop();

            if (!processedForward[currentNode]) {
                processedForward[currentNode] = true;

                for (const Edge& edge : adjList[currentNode]) {
                    uint32_t newDist = currentDist + edge.weight;
                    if (newDist < distForward[edge.target]) {
                        distForward[edge.target] = newDist;
                        prevForward[edge.target] = currentNode;
                        pqForward.emplace(newDist, edge.target);
                    }

                    if (processedBackward[edge.target] && distForward[edge.target] + distBackward[edge.target] < bestCost) {
                        bestCost = distForward[edge.target] + distBackward[edge.target];
                        meetingNode = edge.target;
                    }
                }
            }
        }

        // Process backward search
        if (!pqBackward.empty()) {
            auto [currentDist, currentNode] = pqBackward.top();
            pqBackward.pop();

            if (!processedBackward[currentNode]) {
                processedBackward[currentNode] = true;

                for (const Edge& edge : adjList[currentNode]) {
                    uint32_t newDist = currentDist + edge.weight;
                    if (newDist < distBackward[edge.target]) {
                        distBackward[edge.target] = newDist;
                        prevBackward[edge.target] = currentNode;
                        pqBackward.emplace(newDist, edge.target);
                    }

                    if (processedForward[edge.target] && distForward[edge.target] + distBackward[edge.target] < bestCost) {
                        bestCost = distForward[edge.target] + distBackward[edge.target];
                        meetingNode = edge.target;
                    }
                }
            }
        }

        // Early termination condition
        if (meetingNode != -1 && bestCost < pqForward.top().first + pqBackward.top().first) {
            break;
        }
    }

    if (meetingNode == -1) {
        totalTime = 0;
        return {};
    }

    totalTime = bestCost;

    // Reconstruct the path
    std::vector<int> path;
    for (int node = meetingNode; node != -1; node = prevForward[node]) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());

    for (int node = prevBackward[meetingNode]; node != -1; node = prevBackward[node]) {
        path.push_back(node);
    }

    return path;
}