#ifndef BFS_H
#define BFS_H

#include "CampusGraph.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Stores the results of BFS.
struct BFSResult {
    bool found = false;
    vector<string> visitOrder;
    vector<int> distances;
    int reachableCount = 0;
};

// Stores the shortest path.
struct PathResult {
    bool found = false;
    vector<string> path;
    int connections = -1;
};

// BFS functions.
BFSResult breadthFirstSearch(CampusGraph& graph, string start);
PathResult shortestPath(CampusGraph& graph, string start, string destination);

// Display results.
void displayBFS(BFSResult result);
void displayPath(PathResult result, string start, string destination);

#endif
