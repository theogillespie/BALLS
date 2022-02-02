#pragma once

#include "Interpolation.h"

#include<vector>
#include<algorithm>

double vectorIncludes(std::vector<double>* vec, double n) {
    auto i = std::find(vec->begin(), vec->end(), n);
    if (i != vec->end())
    {
        return i - vec->begin();
    }
    return -1;
};

int vectorClosest(std::vector<double>* vec, double n) {
    auto i = std::lower_bound(vec->begin(), vec->end(), n);
    if (i == vec->end()) { return -1; }

    return *i;
}

struct Curve {
    std::vector<double> x;
    std::vector<double> y;

    double* xMax;
    double* xMin;
    
    
    Curve(std::vector<double> _x, std::vector<double> _y) {
        this->x = _x;
        this->y = _y;

        this->xMin = &this->x[0];
        this->xMax = &this->x[this->x.size()-1];
    };

    // uses interpolation
    double getValue(double _x) {

        if(_x <= *this->xMin) {
            return *this->xMin;
        }
        if(_x >= *this->xMax) {
            return *this->xMax;
        }

        double index = vectorIncludes(&this->x, _x);
        if(index != 0) {
            return this->y[index];
        }

        int x1 = vectorClosest(&this->x, _x);
        int x2 = ++x1;
        return Interpolate::lerp2(_x, this->x[x1], this->y[x1], this->x[x2], this->y[x2]);
    };

};