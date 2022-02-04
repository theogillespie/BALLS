#pragma once


#include "Projectile.h"

#define ENDCONDITION_NEGY 0 


#ifndef ENDCONDITION
#warning Missing a Specified End Condition, using default
#define ENDCONDITION ENDCONDITION_NEGY
#endif // !ENDCONDITION


class EndCondition {
	static void evaluate(Projectile* proj) {

	}
};