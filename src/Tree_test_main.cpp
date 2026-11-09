// tree_test_main.cpp
// Purpose: Standalone driver for testing the department tree on its own
//          (before it is merged into the team's main.cpp). Loads
//          departments.txt from a data directory and offers only the
//          department options.
//          Build:  g++ -std=c++17 -Wall -Iinclude src/StringUtils.cpp
//                  src/DepartmentTree.cpp src/DepartmentMenu.cpp
//                  src/tree_test_main.cpp -o tree_test
//          Run:    ./tree_test [dataDir] 
// Author:  Dabira Olubobola (Member C)

#include "DepartmentTree.h"
#include "DepartmentMenu.h"
#include "StringUtils.h"

#include <iostream>
#include <string>

// Reads a menu choice; returns -1 for blank, text, or trailing junk.
static int readChoice() {
    std::string line;
    if (!std::getline(std::cin, line)) return 0;  // EOF -> exit
    line = trim(line);
    if (line.empty()) return -1;
    for (std::size_t i = 0; i < line.size(); ++i) {
        if (line[i] < '0' || line[i] > '9') return -1;
    }
    if (line.size() > 3) return -1;
    return std::stoi(line);
}

int main(int argc, char* argv[]) {
    std::string dataDir = (argc > 1) ? argv[1] : "data";
    if (!dataDir.empty() && dataDir[dataDir.size() - 1] != '/') dataDir += '/';

    DepartmentTree tree;
    tree.loadFromFile(dataDir + "departments.txt", "departments.txt");

    while (true) {
        std::cout << "\n--- Department Test Menu ---\n"
                  << " 9. Add department\n"
                  << "10. Search department\n"
                  << "11. Display department hierarchy\n"
                  << "12. Preorder traversal\n"
                  << "13. Postorder traversal\n"
                  << "14. Level-order traversal\n"
                  << "15. Department statistics\n"
                  << " 0. Exit\n"
                  << "Choice: ";
        int choice = readChoice();
        switch (choice) {
            case 9:  handleAddDepartment(tree); break;
            case 10: handleSearchDepartment(tree); break;
            case 11: handleDisplayHierarchy(tree); break;
            case 12: handlePreorder(tree); break;
            case 13: handlePostorder(tree); break;
            case 14: handleLevelOrder(tree); break;
            case 15: handleDepartmentStatistics(tree); break;
            case 0:  std::cout << "Goodbye." << std::endl; return 0;
            default: std::cout << "Invalid choice. Please enter a listed number." << std::endl;
        }
    }
}
