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

    if (source < 0 || source >= static_cast<int>(adjList.size()) ||
        target < 0 || target >= static_cast<int>(adjList.size())) {
        throw std::out_of_range("Source or target node is out of bounds.");
    }

    size_t n = adjList.size();
    std::vector<int> distForward(n, INF), distBackward(n, INF);
    std::vector<int> prevForward(n, -1), prevBackward(n, -1);

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

    // Process nodes alternately in forward and backward directions
    while (!pqForward.empty() && !pqBackward.empty()) {
        // Expand forward
        if (!pqForward.empty()) {
            auto [currentF, current] = pqForward.top();
            pqForward.pop();

            if (currentF > distForward[current]) continue;

            for (const Edge& edge : adjList[current]) {
                int neighbor = edge.target;
                int newDist = distForward[current] + edge.weight;

                if (newDist < distForward[neighbor]) {
                    distForward[neighbor] = newDist;
                    prevForward[neighbor] = current;
                    pqForward.emplace(newDist, neighbor);
                }

                if (distBackward[neighbor] < INF) {
                    int potentialCost = distForward[neighbor] + distBackward[neighbor];
                    if (potentialCost < bestCost) {
                        bestCost = potentialCost;
                        meetingNode = neighbor;
                    }
                }
            }
        }

        // Expand backward
        if (!pqBackward.empty()) {
            auto [currentB, currentBack] = pqBackward.top();
            pqBackward.pop();

            if (currentB > distBackward[currentBack]) continue;

            for (const Edge& edge : adjList[currentBack]) {
                int neighbor = edge.target;
                int newDist = distBackward[currentBack] + edge.weight;

                if (newDist < distBackward[neighbor]) {
                    distBackward[neighbor] = newDist;
                    prevBackward[neighbor] = currentBack;
                    pqBackward.emplace(newDist, neighbor);
                }

                if (distForward[neighbor] < INF) {
                    int potentialCost = distForward[neighbor] + distBackward[neighbor];
                    if (potentialCost < bestCost) {
                        bestCost = potentialCost;
                        meetingNode = neighbor;
                    }
                }
            }
        }

        // Terminate if the best cost is finalized
        if (meetingNode != -1) break;
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
