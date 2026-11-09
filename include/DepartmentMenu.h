// DepartmentMenu.h
// Purpose: Menu handlers for the department options. Each function prompts
//          the user (names may contain spaces), validates input, calls the
//          DepartmentTree, and returns so main.cpp can redisplay the menu.
// Author:  Dabira olubobola (Member C)

#ifndef DEPARTMENT_MENU_H
#define DEPARTMENT_MENU_H

#include "DepartmentTree.h"

// Final menu option 9 (M1 option 6): add a department (root if tree is empty).
void handleAddDepartment(DepartmentTree& tree);

// Final menu option 10 (M1 option 7): search a department by name.
void handleSearchDepartment(const DepartmentTree& tree);

// Final menu option 11 (M1 option 8): indented hierarchy.
void handleDisplayHierarchy(const DepartmentTree& tree);

// Final menu option 12 (M1 option 9): preorder sequence.
void handlePreorder(const DepartmentTree& tree);

// Final menu option 13: postorder sequence.
void handlePostorder(const DepartmentTree& tree);

// Final menu option 14: level-order sequence.
void handleLevelOrder(const DepartmentTree& tree);

// Final menu option 15: department statistics.
void handleDepartmentStatistics(const DepartmentTree& tree);

#endif
