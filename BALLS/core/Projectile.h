#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Constants.h"
#include "Logger.h"
#include "Curve.h"
#include "Atmosphere.h"
#include "../io/io.h"

#include <vector>
#include <cmath>
#include <string>

class Effect;

class Projectile {

public:

	string name;

	Vector3 acceleration;
	Vector3 position;
	Vector3 velocity;
	Vector3 forces;

	Vector3 eulerAngles;
	Quaternion rotation;
	Vector3 angularVelocity;
	Vector3 angularAcceleration;
	Vector3 torque;
	Vector3 angularMass;

	Curve drag;

	double dt;
	double elaspedTime;
	double mass;

	std::vector<Effect*> effects = std::vector<Effect*>();
	
	
	Projectile(double mass, double dt=0.001, Vector3 const& initalPosition=Vector3::zero()) {
		this->position = initalPosition;
	};

	Projectile() {};

	~Projectile() {
		this->effects.clear();
	};

	static Projectile fromFile(std::string filepath) {
		ProjectileConfigField name("name");
		ProjectileConfigField mass("mass");
		ProjectileConfigField cdFile("cd");

		vector<ProjectileConfigField*> fields {&name, &mass, &cdFile};
		ProjectileLoader pl(filepath, fields);

		pl.load();
		CurveReader cr(cdFile.valueS);
		vector<double> x, y;
		cr.parse(&x, &y);

		Curve drag(x, y);
		Projectile proj(mass.valueD);

		proj.drag = drag;
		proj.name = name.valueS;
		proj.mass = mass.valueD;

		return proj;
	};

	void addEffect(Effect* effect) {
		this->effects.push_back(effect);
	};

	double kineticEnergy() {
		return (this->velocity * this->velocity).magnitude() * .5 * this->mass;
	};

	double altitude() {
		if (this->position.z > MAXALT) {
			Console::error("WARNING: Projectiles Altitude exceeds supported limit (" + to_string(MAXALT) + "m), results may be inaccurate");
		}
		return this->position.z;
	};

	void addForce(Vector3 const& force) {
		this->forces += force;
	};

	// accounts for rotation
	void addRelativeForce(Vector3 const& force) {
		this->forces += this->toLocalSpace(force);
	}

	Vector3 toLocalSpace(Vector3 vec) {
		Quaternion q(0, vec.x, vec.y, vec.z);
		Quaternion n = this->rotation * q * this->rotation.conjugate();
		return Vector3(n.x, n.y, n.z);
	};

	Vector3 toGlobalSpace(Vector3 vec) {
		Quaternion q(0, vec.x, vec.y, vec.z);
		Quaternion n = this->rotation.conjugate() * q * this->rotation;
		return Vector3(n.x, n.y, n.z);
	}

	void update() {


		// velocity verlet
		this->acceleration += this->forces / this->mass;
		this->position += this->velocity * this->dt + this->acceleration * 0.5 * (this->dt * this->dt);
		this->velocity += this->acceleration * this->dt;

		// currently broken....

		/*
		this->angularAcceleration = this->torque / this->angularMass;
		this->rotation = this->angularVelocity * this->dt + this->angularAcceleration * 0.5 * (this->dt * this->dt);
		this->angularVelocity = this->angularAcceleration * this->dt;
		*/

		this->eulerAngles = this->rotation.toEulerAngles();

		this->torque = Vector3::zero();
		this->forces = Vector3::zero();
		this->acceleration = Vector3::zero();
	};
};

