#pragma once

#include "Vector3.h"
#include "Effects.h"
#include "Projectile.h"

#include <vector>


class Projectile {

public:

	Vector3 acceleration;
	Vector3 position;
	Vector3 velocity;
	Vector3 forces;

	Vector3 rotation;
	Vector3 angularVelocity;
	Vector3 angularAcceleration;
	Vector3 torque;
	Vector3 angularMass;

	double dt;
	double elaspedTime;
	double mass;

	std::vector<Effect> effects = std::vector<Effect>();
	
	
	Projectile(double mass, double dt=0.001, Vector3 const& initalPosition=Vector3::zero()) {
		this->position = initalPosition;
	};

	Projectile() {};

	~Projectile() {
		this->effects.clear();
	};

	void addEffect(Effect effect) {
		this->effects.push_back(effect);
	};

	double kineticEnergy() {
		return (this->velocity * this->velocity).magnitude() * .5 * this->mass;
	}

	double altitude() {
		return this->position.z;
	}

	void addForce(Vector3 const& force) {
		this->forces += force;
	}

	static Vector3 toLocalSpace(Vector3 vec) {
		
	}

	void update() {

		this->acceleration = this->forces / this->mass;
		this->position = this->velocity * this->dt + this->acceleration * 0.5 * (this->dt * this->dt);
		this->velocity = this->acceleration * this->dt;


		//is this illegal?
		this->angularAcceleration = this->torque / this->angularMass;
		this->rotation = this->angularVelocity * this->dt + this->angularAcceleration * 0.5 * (this->dt * this->dt);
		this->angularVelocity = this->angularAcceleration * this->dt;

		this->torque = Vector3::zero();
		this->forces = Vector3::zero();
	}
};