#pragma once

#include <limits>

// Represents a number that is either an int or a float.

struct Number {
    bool isFloat = false;
    bool isInt = false;
    int iVal = std::numeric_limits<int>::infinity();
    double fVal = std::numeric_limits<double>::infinity();
};
