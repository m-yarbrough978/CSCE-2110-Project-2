#include "BFS.h"

#include <queue>

using namespace std;

// Breadth-First Search.
BFSResult breadthFirstSearch(CampusGraph& graph, string start) {

    BFSResult result;

    int startIndex = graph.findBuilding(start);

    // Check if building exists.
    if (startIndex == -1) {
        return result;
    }

    result.found = true;

    int size = graph.buildings.size();

    vector<bool> visited(size, false);

    result.distances.resize(size, -1);

    queue<int> pending;

    // Start BFS.
    visited[startIndex] = true;
    result.distances[startIndex] = 0;

    pending.push(startIndex);

    while (!pending.empty()) {

        int current = pending.front();
        pending.pop();

        // Add building to visit order.
        result.visitOrder.push_back(
            graph.buildings[current].name
        );

        // Check all neighbors.
        for (int i = 0;
             i < graph.buildings[current].neighbors.size(); i++) {

            int next = graph.buildings[current].neighbors[i];

            if (!visited[next]) {

                visited[next] = true;

                result.distances[next] =
                    result.distances[current] + 1;

                pending.push(next);
            }
        }
    }

    result.reachableCount = result.visitOrder.size();

    return result;
}

// Find the shortest path using BFS.
PathResult shortestPath(CampusGraph& graph, string start, string destination) {

    PathResult result;

    int startIndex = graph.findBuilding(start);
    int endIndex = graph.findBuilding(destination);

    // Make sure both buildings exist.
    if (startIndex == -1 || endIndex == -1) {
        return result;
    }

    int size = graph.buildings.size();

    vector<bool> visited(size, false);

    vector<int> parent(size, -1);

    queue<int> pending;

    visited[startIndex] = true;
    pending.push(startIndex);

    // Search for destination.
    while (!pending.empty()) {

        int current = pending.front();
        pending.pop();

        if (current == endIndex) {
            break;
        }

        for (int i = 0;
             i < graph.buildings[current].neighbors.size(); i++) {

            int next = graph.buildings[current].neighbors[i];

            if (!visited[next]) {

                visited[next] = true;

                parent[next] = current;

                pending.push(next);
            }
        }
    }

    // No path exists.
    if (!visited[endIndex]) {
        return result;
    }

    result.found = true;

    // Build the path backward.
    vector<int> reversePath;

    int current = endIndex;

    while (current != -1) {

        reversePath.push_back(current);

        current = parent[current];
    }

    // Reverse the path to get the correct order.
    for (int i = reversePath.size() - 1; i >= 0; i--) {

        result.path.push_back(
            graph.buildings[reversePath[i]].name
        );
    }

    result.connections = result.path.size() - 1;

    return result;
}

// Display BFS results.
void displayBFS(CampusGraph& graph, BFSResult result) {

    if (!result.found) {
        cout << "Starting building was not found." << endl;
        return;
    }

    cout << "\nBFS Visit Order:\n";

    for (int i = 0; i < result.visitOrder.size(); i++) {

        string name = result.visitOrder[i];

        int index = graph.findBuilding(name);

        cout << name << " - Distance: " << result.distances[index] << endl;
    }

    cout << "Reachable buildings: "
         << result.reachableCount << endl;
}

// Display shortest path results.
void displayPath(PathResult result, string start, string destination) {

    if (!result.found) {
        cout << "No path found from "
             << start << " to "
             << destination << endl;

        return;
    }

    cout << "\nShortest Path:\n";

    for (int i = 0; i < result.path.size(); i++) {

        cout << result.path[i] << endl;
    }

    cout << "Total connections: "
         << result.connections << endl;
}
