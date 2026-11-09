// StringUtils.cpp
// Purpose: Implementation of the shared string helpers (see StringUtils.h).
// Author: Dabira Olubobola  (Member C) - shared utility

#include "StringUtils.h"

// Whitespace set required by Section 4.1 (includes \r for Windows files).
static const char* WHITESPACE = " \t\r\n";

// Removes leading and trailing whitespace; internal spaces are preserved.
std::string trim(const std::string& s) {
    std::string::size_type first = s.find_first_not_of(WHITESPACE);
    if (first == std::string::npos) return "";
    std::string::size_type last = s.find_last_not_of(WHITESPACE);
    return s.substr(first, last - first + 1);
}

// Converts ASCII uppercase letters to lowercase.
std::string toLower(const std::string& s) {
    std::string out = s;
    for (std::string::size_type i = 0; i < out.size(); ++i) {
        if (out[i] >= 'A' && out[i] <= 'Z') out[i] = static_cast<char>(out[i] - 'A' + 'a');
    }
    return out;
}

// Converts ASCII lowercase letters to uppercase.
std::string toUpper(const std::string& s) {
    std::string out = s;
    for (std::string::size_type i = 0; i < out.size(); ++i) {
        if (out[i] >= 'a' && out[i] <= 'z') out[i] = static_cast<char>(out[i] - 'a' + 'A');
    }
    return out;
}

// Case-insensitive equality; lengths must match so internal spaces matter.
bool equalsIgnoreCase(const std::string& a, const std::string& b) {
    return a.size() == b.size() && toLower(a) == toLower(b);
}

// Splits on '|' and trims each field. Empty fields are kept so the caller
// can detect wrong field counts and empty required fields.
std::vector<std::string> splitFields(const std::string& line) {
    std::vector<std::string> fields;
    std::string current;
    for (std::string::size_type i = 0; i < line.size(); ++i) {
        if (line[i] == '|') {
            fields.push_back(trim(current));
            current.clear();
        } else {
            current += line[i];
        }
    }
    fields.push_back(trim(current));
    return fields;
}

// A comment line starts with '#' after optional whitespace; '#' elsewhere is text.
bool isBlankOrComment(const std::string& line) {
    std::string t = trim(line);
    return t.empty() || t[0] == '#';
}
