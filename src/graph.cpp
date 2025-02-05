#include "includes/graph.hpp"
#include <stdexcept>

/**
 * Default constructor for the Graph class.
 */
Graph::Graph() {}

/**
 * Adds an edge to the graph.
 * 
 * @param source Source node of the edge.
 * @param target Target node of the edge.
 * @param weight Weight of the edge.
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
 * 
 * @return Maximum node ID.
 */
int Graph::get_max_node_id() const {
    return adjList.size() - 1;
}

/**
 * Finds the shortest path between two nodes using bidirectional Dijkstra's algorithm.
 * 
 * @param source Source node.
 * @param target Target node.
 * @param totalTime Reference to store the total time of the shortest path.
 * @return Vector of node IDs representing the shortest path.
 */
std::vector<int> Graph::shortest_path(int source, int target, uint32_t& totalTime) {
    constexpr uint32_t INF = std::numeric_limits<uint32_t>::max();
    int maxNodeId = get_max_node_id();

    if (source >= adjList.size() || target >= adjList.size()) {
        throw std::out_of_range("Source or target node is out of bounds.");
    }

    // Initialize distance and previous node arrays for forward and backward searches
    std::vector<uint32_t> distForward(maxNodeId + 1, INF);
    std::vector<uint32_t> distBackward(maxNodeId + 1, INF);
    std::vector<int> prevForward(maxNodeId + 1, -1);
    std::vector<int> prevBackward(maxNodeId + 1, -1);
    std::vector<bool> processedForward(maxNodeId + 1, false);
    std::vector<bool> processedBackward(maxNodeId + 1, false);

    distForward[source] = 0;
    distBackward[target] = 0;

    // Priority queues for forward and backward searches
    using NodeDistPair = std::pair<uint32_t, int>;
    auto comparator = [](const NodeDistPair& a, const NodeDistPair& b) {
        return a.first > b.first;
    };

    std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, decltype(comparator)> pqForward(comparator), pqBackward(comparator);

    pqForward.emplace(0, source);
    pqBackward.emplace(0, target);

    uint32_t bestCost = INF;
    int meetingNode = -1;

    // Bidirectional Dijkstra's algorithm
    while (!pqForward.empty() && !pqBackward.empty()) {
        auto process = [&](std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, decltype(comparator)>& pq,
                           std::vector<uint32_t>& dist, std::vector<int>& prev, std::vector<bool>& processed,
                           std::vector<uint32_t>& otherDist, std::vector<bool>& otherProcessed, bool isForward) {
            if (!pq.empty()) {
                auto [currentDist, currentNode] = pq.top();
                pq.pop();

                if (processed[currentNode]) return;
                processed[currentNode] = true;

                for (const auto& [neighbor, weight] : adjList[currentNode]) {
                    uint32_t newDist = currentDist + weight;
                    if (newDist < dist[neighbor]) {
                        dist[neighbor] = newDist;
                        prev[neighbor] = currentNode;
                        pq.emplace(newDist, neighbor);
                    }
                    if (otherProcessed[neighbor] && dist[neighbor] + otherDist[neighbor] < bestCost) {
                        bestCost = dist[neighbor] + otherDist[neighbor];
                        meetingNode = neighbor;
                    }
                }
            }
        };

        process(pqForward, distForward, prevForward, processedForward, distBackward, processedBackward, true);
        process(pqBackward, distBackward, prevBackward, processedBackward, distForward, processedForward, false);

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