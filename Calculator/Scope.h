#pragma once

#include "Number.h"

// Stores names and values.

class Scope {
    int * iVals;
    double * fVals;
public:
    void init ();
    void put (const char * name, int val);
    void put (const char * name, double val);
    Number get (const char * name);
};
