#pragma once

#include "core.h"

#define ENDCONDITION ENDCONDITION_NEGY

class Simulation {

    void run() {
        Projectile projectile(1, 0.001, Vector3(0, 10, 0));

        while(!EndCondition::evaluate(&projectile)) {
            projectile.update();
        }

    }
};