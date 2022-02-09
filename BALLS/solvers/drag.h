#pragma once


#include "../core/core.h"

class Projectile;

class DragSolver {
public:
    Projectile* projectile;

    DragSolver(Projectile* proj) {
        this->projectile = proj;
    };

    virtual Curve generateCurve() {}
};


class gDrag: DragSolver {
    Curve generateCurve() override {
        return Curve::fromFile("filepath");
    }
};

class mcDrag: DragSolver {
    Curve generateCurve() override {}
};