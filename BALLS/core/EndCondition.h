#pragma once

#include "Projectile.h"

#define ENDCONDITION_NEGY 0 
#define ENDCONDITION_MAXALT 1

#ifndef ENDCONDITION
//#warning Missing a Specified End Condition, using default
#define ENDCONDITION ENDCONDITION_NEGY
#endif // !ENDCONDITION

class EndCondition {
	public:
	static bool evaluate(Projectile* proj) {
		if(proj->position.y < 0) {
			return true;
		}
		return false;
	}
};