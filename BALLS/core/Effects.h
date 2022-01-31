#pragma once

#include "Projectile.h"
#include "Constants.h"
#include "Vector3.h"

#include <cmath>

class Effect {
public:

	Projectile* projectile;

	Effect(Projectile* _projectile) {
		this->projectile = _projectile;
	};

	virtual void update();
};

class Gravity : Effect {

	using Effect::Effect;

	void update() {
		double alt = this->projectile->altitude();
		this->projectile->acceleration.z += G * pow((re / re + alt), 2.0);
	};
};