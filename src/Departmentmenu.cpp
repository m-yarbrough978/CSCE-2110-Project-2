// DepartmentMenu.cpp
// Purpose: Implementation of the department menu handlers.
// Author:  Dabira Olubobola (Member C)  

#include "DepartmentMenu.h"
#include "StringUtils.h"

#include <iostream>
#include <string>

// Reads a full line (spaces allowed) and trims it. Returns false on EOF.
static bool readName(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        out.clear();
        return false;
    }
    out = trim(line);
    return true;
}

// Adds the root when the tree is empty (no parent prompt); otherwise asks
// for an existing parent. Errors name the problem and leave the tree unchanged.
void handleAddDepartment(DepartmentTree& tree) {
    std::string name;
    readName("Enter new department name: ", name);
    if (name.empty()) {
        std::cout << "Error: department name cannot be blank." << std::endl;
        return;
    }

    if (tree.isEmpty()) {
        tree.addRoot(name);
        std::cout << "Tree was empty. '" << name << "' added as the root department." << std::endl;
        return;
    }

    if (tree.find(name) != nullptr) {
        std::cout << "Error: a department named '" << tree.find(name)->name
                  << "' already exists. Tree unchanged." << std::endl;
        return;
    }

    std::string parent;
    readName("Enter parent department name: ", parent);
    if (parent.empty()) {
        std::cout << "Error: parent name cannot be blank." << std::endl;
        return;
    }

    AddResult result = tree.addDepartment(name, parent);
    switch (result) {
        case ADD_OK:
            std::cout << "Added '" << name << "' under '"
                      << tree.find(parent)->name << "'." << std::endl;
            break;
        case ADD_UNKNOWN_PARENT:
            std::cout << "Error: unknown parent department '" << parent
                      << "'. Tree unchanged." << std::endl;
            break;
        case ADD_DUPLICATE_NAME:
            std::cout << "Error: duplicate department name '" << name
                      << "'. Tree unchanged." << std::endl;
            break;
        default:
            std::cout << "Error: could not add department. Tree unchanged." << std::endl;
            break;
    }
}

// Prompts for a name and prints name, parent, child count, depth.
void handleSearchDepartment(const DepartmentTree& tree) {
    std::string name;
    readName("Enter department name to search: ", name);
    if (name.empty()) {
        std::cout << "Error: department name cannot be blank." << std::endl;
        return;
    }
    tree.printSearchResult(name);
}

// Shows the indented preorder hierarchy.
void handleDisplayHierarchy(const DepartmentTree& tree) {
    std::cout << "Department hierarchy:" << std::endl;
    tree.displayHierarchy();
}

// Shows the preorder sequence without indentation.
void handlePreorder(const DepartmentTree& tree) {
    tree.printTraversal("Preorder traversal", tree.preorder());
}

// Shows the postorder sequence.
void handlePostorder(const DepartmentTree& tree) {
    tree.printTraversal("Postorder traversal", tree.postorder());
}

// Shows the level-order sequence.
void handleLevelOrder(const DepartmentTree& tree) {
    tree.printTraversal("Level-order traversal", tree.levelOrder());
}

// Shows total departments, leaves, and height.
void handleDepartmentStatistics(const DepartmentTree& tree) {
    std::cout << "Department statistics:" << std::endl;
    tree.printStatistics();
}
