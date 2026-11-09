//DepartmentTree.h
// Purpose: General tree holding the academic department hierarchy.
//          Supports loading from departments.txt, adding departments,
//          case-insensitive search, an indented hierarchy display,
//          preorder / postorder / level-order traversals, and statistics
//          (total departments, leaves, height).
// Author:  Dabira olubobola (Member C)

#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <string>
#include <vector>
#include "DepartmentNode.h"

// Result codes for addDepartment so callers can print a precise message.
enum AddResult {
    ADD_OK,
    ADD_EMPTY_NAME,
    ADD_DUPLICATE_NAME,
    ADD_UNKNOWN_PARENT,
    ADD_ROOT_ALREADY_EXISTS,  // tried to add a second root (parent NONE)
    ADD_ROOT_NEEDS_NONE       // first file record did not use NONE as parent
};

class DepartmentTree {
public:
    // Creates an empty tree.
    DepartmentTree();

    // Frees every node (postorder delete).
    ~DepartmentTree();

    // Copying is disabled because the tree owns raw node pointers.
    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    // Loads records from a departments file. Prints a warning for every
    // rejected line (filename, line number, reason) and a load summary.
    // A missing file prints an error and leaves the tree empty.
    void loadFromFile(const std::string& path, const std::string& displayName);

    // Adds the root. Fails if the name is empty or a root already exists.
    AddResult addRoot(const std::string& name);

    // Adds a child under an existing parent (matched ignoring case).
    AddResult addDepartment(const std::string& name, const std::string& parentName);

    // Returns the node whose name matches ignoring case, or nullptr.
    DepartmentNode* find(const std::string& name) const;

    // Number of edges from the root to the node (root = 0).
    int depthOf(const DepartmentNode* node) const;

    // True if no departments are loaded.
    bool isEmpty() const { return root == nullptr; }

    // Prints name, parent (None for root), direct-child count, and depth.
    void printSearchResult(const std::string& name) const;

    // Prints the hierarchy in preorder, indented 4 spaces per depth level.
    void displayHierarchy() const;

    // Traversals return names in visit order (siblings in insertion order).
    std::vector<std::string> preorder() const;
    std::vector<std::string> postorder() const;
    std::vector<std::string> levelOrder() const;   // uses std::queue

    // Prints a traversal sequence (no indentation) with a title.
    void printTraversal(const std::string& title,
                        const std::vector<std::string>& names) const;

    // Statistics.
    int countNodes() const;
    int countLeaves() const;
    int height() const;            // -1 for an empty tree
    void printStatistics() const;  // shows "N/A" height when empty

private:
    DepartmentNode* root;

    // Recursive helpers.
    void destroy(DepartmentNode* node);
    DepartmentNode* findHelper(DepartmentNode* node, const std::string& name) const;
    void displayHelper(const DepartmentNode* node, int depth) const;
    void preorderHelper(const DepartmentNode* node, std::vector<std::string>& out) const;
    void postorderHelper(const DepartmentNode* node, std::vector<std::string>& out) const;
    int countNodesHelper(const DepartmentNode* node) const;
    int countLeavesHelper(const DepartmentNode* node) const;
    int heightHelper(const DepartmentNode* node) const;
};

#endif
