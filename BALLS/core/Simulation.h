#pragma once

#include "EndCondition.h"
#include "core.h"

#define ENDCONDITION ENDCONDITION_NEGY

class Simulation {

public:
    static Projectile* run() {
        Projectile projectile(1, 0.001, Vector3(0, 10, 0));
    
        while(!EndCondition::evaluate(&projectile)) {
            projectile.update();
        }

        Console::print("done sim:");
        Console::print(projectile.position.toString());
        return &projectile;
    }
};