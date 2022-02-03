#pragma once

#include "../core/Curve.h"
#include <string>
#include <fstream>

using namespace std;

class CurveWriter {
public:
    static void write(string filepath, Curve* curve) {
        ifstream ifs(filepath, ifstream::out);
        
    }
};