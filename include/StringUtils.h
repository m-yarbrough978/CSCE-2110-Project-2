// StringUtils.h
// Purpose: Small shared string helpers used by every loader and menu prompt:
//          trimming (spaces, tabs, \r, \n), case-insensitive comparison,
//          uppercase/lowercase conversion, and splitting on '|'.
// Author:  Dabira olubobola (Member C)

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

// Removes leading/trailing spaces, tabs, carriage returns and newlines.
std::string trim(const std::string& s);

// Returns an all-lowercase copy (ASCII letters only).
std::string toLower(const std::string& s);

// Returns an all-uppercase copy (ASCII letters only).
std::string toUpper(const std::string& s);

// True if a and b are equal ignoring ASCII capitalization.
bool equalsIgnoreCase(const std::string& a, const std::string& b);

// Splits a line on '|' and trims every field. "a||b" gives 3 fields.
std::vector<std::string> splitFields(const std::string& line);

// True if the line is blank or its first non-whitespace character is '#'.
bool isBlankOrComment(const std::string& line);

#endif 
