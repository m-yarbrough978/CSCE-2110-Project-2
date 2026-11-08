#include "CampusGraph.h"
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Make names lowercase so capitalization does not matter
string makeLower(string name) {

    for (int i = 0; i < name.length(); i++) {
        name[i] = tolower(name[i]);
    }

    return name;
}

// Find a building by name
int CampusGraph::findBuilding(string name) {

    name = makeLower(name);

    for (int i = 0; i < buildings.size(); i++) {

        if (makeLower(buildings[i].name) == name) {
            return i;
        }
    }

    return -1;
}

// Add a building if it does not already exist.
void CampusGraph::addBuilding(string name) {

    if (name == "" || findBuilding(name) != -1) {
        return;
    }

    Building newBuilding;

    newBuilding.name = name;

    buildings.push_back(newBuilding);
}

// Add a connection between two buildings.
void CampusGraph::addConnection(
    string building1,
    string building2
) {

    int first = findBuilding(building1);
    int second = findBuilding(building2);

    if (first == -1 || second == -1 || first == second) {
        return;
    }

    // Check for duplicate connections.
    for (int i = 0; i < buildings[first].neighbors.size(); i++) {

        if (buildings[first].neighbors[i] == second) {
            return;
        }
    }

    // Add the connection in both directions.
    buildings[first].neighbors.push_back(second);
    buildings[second].neighbors.push_back(first);

    totalConnections++;
}

// Load buildings from a file.
void CampusGraph::loadBuildings(string filename) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
        return;
    }

    string name;

    while (getline(file, name)) {

        if (name == "" || name[0] == '#') {
            continue;
        }

        if (findBuilding(name) != -1) {
            cout << "Warning: duplicate building: "
                 << name << endl;
        }
        else {
            addBuilding(name);
        }
    }

    file.close();

    cout << "Buildings loaded: "
         << buildings.size() << endl;
}

// Load connections from a file.
void CampusGraph::loadConnections(string filename) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        if (line == "" || line[0] == '#') {
            continue;
        }

        int divider = line.find('|');

        if (divider == -1) {
            cout << "Invalid connection: "
                 << line << endl;
            continue;
        }

        string building1 = line.substr(0, divider);
        string building2 = line.substr(divider + 1);

        int oldCount = totalConnections;

        addConnection(building1, building2);

        if (totalConnections > oldCount) {
            cout << "Connection loaded: "
            << building1 << " - "
            << building2 << endl;
        }
        else {
            cout << "Warning: invalid or duplicate connection: " << line << endl;
        }
    }

    file.close();

    cout << "Connections loaded: " << totalConnections << endl;
}

// Display all buildings and their connections.
void CampusGraph::displayGraph() {

    for (int i = 0; i < buildings.size(); i++) {

        cout << buildings[i].name << ": ";

        for (int j = 0; j < buildings[i].neighbors.size(); j++) {

            int neighbor = buildings[i].neighbors[j];

            cout << buildings[neighbor].name << " ";
        }

        cout << endl;
    }
}

// Display total buildings and connections.
void CampusGraph::displayCounts() {

    cout << "Total buildings: " << buildings.size() << endl;

    cout << "Total connections: " << totalConnections << endl;

    for (int i = 0; i < buildings.size(); i++) {

        cout << buildings[i].name << " has " << buildings[i].neighbors.size()
             << " connections." << endl;
    }
}

// Display connected components and isolated buildings.
void CampusGraph::displayConnectivity() {

    vector<bool> visited(buildings.size(), false);

    int components = 0;

    for (int i = 0; i < buildings.size(); i++) {

        if (buildings[i].neighbors.size() == 0) {
            cout << "Isolated building: "
                 << buildings[i].name << endl;
        }

        if (!visited[i]) {

            components++;

            vector<int> pending;
            pending.push_back(i);

            visited[i] = true;

            while (!pending.empty()) {

                int current = pending.back();
                pending.pop_back();

                for (int j = 0;
                     j < buildings[current].neighbors.size(); j++) {

                    int next = buildings[current].neighbors[j];

                    if (!visited[next]) {
                        visited[next] = true;
                        pending.push_back(next);
                    }
                }
            }
        }
    }

    cout << "Connected components: "
         << components << endl;
}
