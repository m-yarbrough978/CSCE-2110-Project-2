// DepartmentNode.h
// Purpose: Defines one node of the general (n-ary) department tree.
//          Each node stores a department name, a pointer to its parent,
//          and any number of children kept in insertion order.
// Author:  Dabira Olubobola (Member C)

#ifndef DEPARTMENT_NODE_H
#define DEPARTMENT_NODE_H

#include <string>
#include <vector>

struct DepartmentNode {
    std::string name;                       // spelling from the first accepted record
    DepartmentNode* parent;                 // nullptr for the root
    std::vector<DepartmentNode*> children;  // siblings in insertion order

    // Creates a node with the given name and parent (no children yet).
    DepartmentNode(const std::string& n, DepartmentNode* p)
        : name(n), parent(p) {}
};

#endif
