// Purpose: Implementation of the general department tree (see DepartmentTree.h).
// Author:  Dabira Olubobola (Member C)

#include "DepartmentTree.h"
#include "StringUtils.h"

#include <fstream>
#include <iostream>
#include <queue>

// Starts with no root (empty tree).
DepartmentTree::DepartmentTree() : root(nullptr) {}

// Releases all nodes.
DepartmentTree::~DepartmentTree() {
    destroy(root);
    root = nullptr;
}

// Deletes children first, then the node itself (postorder).
void DepartmentTree::destroy(DepartmentNode* node) {
    if (node == nullptr) return;
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        destroy(node->children[i]);
    }
    delete node;
}

// ---------------------------------------------------------------------------
// Loading
// ---------------------------------------------------------------------------

// Reads departments.txt line by line with getline, validates each record
// using the Section 5.5 rules, and prints warnings plus a load summary.
void DepartmentTree::loadFromFile(const std::string& path, const std::string& displayName) {
    std::ifstream in(path.c_str());
    if (!in) {
        std::cout << "ERROR: Could not open " << displayName
                  << " (" << path << "). Treating it as empty." << std::endl;
        std::cout << displayName << ": 0 accepted, 0 rejected" << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (std::getline(in, line)) {
        ++lineNumber;
        if (isBlankOrComment(line)) continue;

        std::vector<std::string> fields = splitFields(line);
        std::string reason;

        if (fields.size() != 2) {
            reason = "expected 2 fields (DepartmentName|ParentName), found "
                     + std::to_string(fields.size());
        } else if (fields[0].empty()) {
            reason = "department name is empty";
        } else if (fields[1].empty()) {
            reason = "parent name is empty";
        } else {
            const std::string& name = fields[0];
            const std::string& parent = fields[1];
            bool parentIsNone = equalsIgnoreCase(parent, "NONE");
            AddResult result;

            if (parentIsNone) {
                result = addRoot(name);
            } else if (root == nullptr) {
                result = ADD_ROOT_NEEDS_NONE;
            } else {
                result = addDepartment(name, parent);
            }

            switch (result) {
                case ADD_OK: break;
                case ADD_EMPTY_NAME:
                    reason = "department name is empty"; break;
                case ADD_DUPLICATE_NAME:
                    reason = "duplicate department name '" + name + "'"; break;
                case ADD_UNKNOWN_PARENT:
                    reason = "unknown parent '" + parent + "' (not accepted on an earlier line)"; break;
                case ADD_ROOT_ALREADY_EXISTS:
                    reason = "a root department already exists; parent NONE is only allowed for the first department"; break;
                case ADD_ROOT_NEEDS_NONE:
                    reason = "first department must use NONE as parent; unknown parent '" + parent + "'"; break;
            }
        }

        if (reason.empty()) {
            ++accepted;
        } else {
            ++rejected;
            std::cout << "WARNING: " << displayName << " line " << lineNumber
                      << ": " << reason << std::endl;
        }
    }

    std::cout << displayName << ": " << accepted << " accepted, "
              << rejected << " rejected" << std::endl;
}

// ---------------------------------------------------------------------------
// Insertion and search
// ---------------------------------------------------------------------------

// Creates the root if the tree is empty.
AddResult DepartmentTree::addRoot(const std::string& name) {
    std::string clean = trim(name);
    if (clean.empty()) return ADD_EMPTY_NAME;
    if (root != nullptr) {
        // A name clash with the existing root is reported as a duplicate.
        if (find(clean) != nullptr) return ADD_DUPLICATE_NAME;
        return ADD_ROOT_ALREADY_EXISTS;
    }
    root = new DepartmentNode(clean, nullptr);
    return ADD_OK;
}

// Appends a new child to the parent's children (keeps insertion order).
AddResult DepartmentTree::addDepartment(const std::string& name, const std::string& parentName) {
    std::string clean = trim(name);
    std::string cleanParent = trim(parentName);
    if (clean.empty()) return ADD_EMPTY_NAME;

    DepartmentNode* parent = find(cleanParent);
    if (parent == nullptr) return ADD_UNKNOWN_PARENT;
    if (find(clean) != nullptr) return ADD_DUPLICATE_NAME;

    parent->children.push_back(new DepartmentNode(clean, parent));
    return ADD_OK;
}

// Public search entry point (trimmed, case-insensitive).
DepartmentNode* DepartmentTree::find(const std::string& name) const {
    return findHelper(root, trim(name));
}

// Recursive preorder search.
DepartmentNode* DepartmentTree::findHelper(DepartmentNode* node, const std::string& name) const {
    if (node == nullptr) return nullptr;
    if (equalsIgnoreCase(node->name, name)) return node;
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        DepartmentNode* found = findHelper(node->children[i], name);
        if (found != nullptr) return found;
    }
    return nullptr;
}

// Counts parent links up to the root.
int DepartmentTree::depthOf(const DepartmentNode* node) const {
    int depth = 0;
    while (node != nullptr && node->parent != nullptr) {
        ++depth;
        node = node->parent;
    }
    return depth;
}

// Prints the details required by TREE-4.
void DepartmentTree::printSearchResult(const std::string& name) const {
    if (root == nullptr) {
        std::cout << "No departments are loaded." << std::endl;
        return;
    }
    DepartmentNode* node = find(name);
    if (node == nullptr) {
        std::cout << "Department not found: " << trim(name) << std::endl;
        return;
    }
    std::cout << "Department found:" << std::endl;
    std::cout << "  Name:        " << node->name << std::endl;
    std::cout << "  Parent:      " << (node->parent ? node->parent->name : "None") << std::endl;
    std::cout << "  Children:    " << node->children.size() << std::endl;
    std::cout << "  Depth:       " << depthOf(node) << std::endl;
}

// ---------------------------------------------------------------------------
// Display and traversals
// ---------------------------------------------------------------------------

// Preorder display with 4 spaces of indentation per depth level.
void DepartmentTree::displayHierarchy() const {
    if (root == nullptr) {
        std::cout << "No departments are loaded." << std::endl;
        return;
    }
    displayHelper(root, 0);
}

// Prints this node indented, then its children in insertion order.
void DepartmentTree::displayHelper(const DepartmentNode* node, int depth) const {
    std::cout << std::string(static_cast<std::size_t>(depth) * 4, ' ') << node->name << std::endl;
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        displayHelper(node->children[i], depth + 1);
    }
}

// Preorder: visit node, then children left to right.
std::vector<std::string> DepartmentTree::preorder() const {
    std::vector<std::string> out;
    preorderHelper(root, out);
    return out;
}

void DepartmentTree::preorderHelper(const DepartmentNode* node, std::vector<std::string>& out) const {
    if (node == nullptr) return;
    out.push_back(node->name);
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        preorderHelper(node->children[i], out);
    }
}

// Postorder: children left to right, then the node.
std::vector<std::string> DepartmentTree::postorder() const {
    std::vector<std::string> out;
    postorderHelper(root, out);
    return out;
}

void DepartmentTree::postorderHelper(const DepartmentNode* node, std::vector<std::string>& out) const {
    if (node == nullptr) return;
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        postorderHelper(node->children[i], out);
    }
    out.push_back(node->name);
}

// Level-order: breadth-first using a queue, siblings in insertion order.
std::vector<std::string> DepartmentTree::levelOrder() const {
    std::vector<std::string> out;
    if (root == nullptr) return out;
    std::queue<const DepartmentNode*> q;
    q.push(root);
    while (!q.empty()) {
        const DepartmentNode* node = q.front();
        q.pop();
        out.push_back(node->name);
        for (std::size_t i = 0; i < node->children.size(); ++i) {
            q.push(node->children[i]);
        }
    }
    return out;
}

// Prints a numbered traversal sequence without indentation.
void DepartmentTree::printTraversal(const std::string& title,
                                    const std::vector<std::string>& names) const {
    if (names.empty()) {
        std::cout << "No departments are loaded." << std::endl;
        return;
    }
    std::cout << title << ":" << std::endl;
    for (std::size_t i = 0; i < names.size(); ++i) {
        std::cout << names[i] << std::endl;
    }
    std::cout << "Total visited: " << names.size() << std::endl;
}

// ---------------------------------------------------------------------------
// Statistics
// ---------------------------------------------------------------------------

int DepartmentTree::countNodes() const { return countNodesHelper(root); }

// Counts this node plus all descendants.
int DepartmentTree::countNodesHelper(const DepartmentNode* node) const {
    if (node == nullptr) return 0;
    int total = 1;
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        total += countNodesHelper(node->children[i]);
    }
    return total;
}

int DepartmentTree::countLeaves() const { return countLeavesHelper(root); }

// A leaf has no children (a root-only tree has one leaf).
int DepartmentTree::countLeavesHelper(const DepartmentNode* node) const {
    if (node == nullptr) return 0;
    if (node->children.empty()) return 1;
    int leaves = 0;
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        leaves += countLeavesHelper(node->children[i]);
    }
    return leaves;
}

int DepartmentTree::height() const { return heightHelper(root); }

// Height in edges: empty = -1, single node = 0.
int DepartmentTree::heightHelper(const DepartmentNode* node) const {
    if (node == nullptr) return -1;
    int best = -1;
    for (std::size_t i = 0; i < node->children.size(); ++i) {
        int h = heightHelper(node->children[i]);
        if (h > best) best = h;
    }
    return best + 1;
}

// Prints TREE-8 statistics, with N/A height for an empty tree.
void DepartmentTree::printStatistics() const {
    if (root == nullptr) {
        std::cout << "No departments are loaded." << std::endl;
        std::cout << "Total departments: 0" << std::endl;
        std::cout << "Leaf departments: 0" << std::endl;
        std::cout << "Tree height: N/A" << std::endl;
        return;
    }
    std::cout << "Total departments: " << countNodes() << std::endl;
    std::cout << "Leaf departments: " << countLeaves() << std::endl;
    std::cout << "Tree height: " << height() << std::endl;
}
