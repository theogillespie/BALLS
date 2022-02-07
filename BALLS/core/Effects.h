#pragma once

#include "Logger.h"
#include "core.h"

class Effect {
public:

	Projectile* projectile;
	Logger* logger;

	Effect(Projectile* proj) {
		this->projectile = proj;
	}

	virtual void update();
};

class Gravity : Effect {

public:
	Gravity(Projectile* proj): Effect(proj) {
		this->logger = new Logger("Gravity Acceleration", &this->projectile->acceleration.y);
	};

	void update() override {
		double alt = this->projectile->altitude();
		this->projectile->acceleration.y += G * pow((re / re + alt), 2.0);
		this->logger->update();
	};
};


//MCDRAG
