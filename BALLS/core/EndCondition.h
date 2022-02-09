#pragma once

#include "Effects.h"
#include "Projectile.h"

class Projectile;

#define ENDCONDITION_NEGY 0 
#define ENDCONDITION_MAXALT 1

#ifndef ENDCONDITION
//#warning Missing a Specified End Condition, using default
#define ENDCONDITION ENDCONDITION_NEGY
#endif // !ENDCONDITION


class EndCondition {
	public:
	static bool evaluate(Projectile* proj) {
		#if ENDCONDITION == ENDCONDITION_NEGY
		if(proj->position.y < 0) {
			return true;
		}
		#elif ENDCONDITION == ENDCONDITION_MAXALT
		if(proj->position.y > MAXALT) {
			return true;
		}
		#endif
	}
};