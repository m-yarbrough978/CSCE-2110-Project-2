#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CampusGraph {
public:

    struct Building {
        string name;
        vector<int> neighbors;
    };

    vector<Building> buildings;
    int totalConnections = 0;

    // Load buildings and connections
    void loadBuildings(string filename);
    void loadConnections(string filename);

    // Add buildings and connections
    void addBuilding(string name);
    void addConnection(string building1, string building2);

    // Search for a building
    int findBuilding(string name);

    // Display graph information
    void displayGraph();
    void displayCounts();
    void displayConnectivity();

};

#endif
