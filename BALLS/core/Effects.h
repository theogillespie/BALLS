#pragma once

#include "Projectile.h"
#include "Constant.h"
#include "Vector3.h"

class Effect {
private:
	Projectile* projectile;
public:

	Effect(Projectile* _projectile) {
		this->projectile = _projectile;
	};

	virtual void update();
};

class Gravity : Effect {
public:
	using Effect : Effect;

	void update() {
		double alt = this->projectile->altitude();

		this->projectile->acceleration.z += G * pow((re / re + alt), 2.0);
	};
};