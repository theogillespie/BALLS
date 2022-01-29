#pragma once

#include<vector>

#include "Vector3.h"
#include "Effects.h

class Projectile {

public:

	std::vector<Effect> effects;

	Vector3 acceleration;
	Vector3 position;
	Vector3 velocity;
	Vector3 forces;

	double dt;
	double elaspedTime;
	double mass;
	
	Projectile(Vector3 const& initalPosition) {

	};

	~Projectile() {
		this->effects.clear();
	};

	void addEffect(Effect effect) {
		this->effects.push_back(effect);
	};

	double kineticEnergy() {
		return .5 * this->mass * (this.velocity * this.velocity);
	}

	void update() {

		for (uint8_t i = 0; i < this->effects.size(); i++) {
			this->effects[i].update();
		}

		this->acceleration = this->forces / this->mass;
		this->position = this->velocity * this->dt + 0.5 * this->acceleration * (this->dt * this->dt);
		this->velocity = this->acceleration.x * this->dt;
	}
};