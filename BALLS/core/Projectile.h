#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Constants.h"
#include "Logger.h"
#include "Curve.h"
#include "../io/ProjectileLoader.h"
#include "../io/CurveReader.h"

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

	Vector3 rotation;
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

		vector<ProjectileConfigField*> fields {&mass, &cdFile};
		ProjectileLoader pl(filepath, fields);

		pl.load();

		CurveReader cr(cdFile.valueS);
		vector<double> x, y;
		cr.parse(&x, &y);

		cout << "parsed curve";

		Curve drag(x, y);
		Projectile proj(mass.valueD);
		proj.drag = drag;
		proj.name = name.valueS;

		return proj;
	};

	void addEffect(Effect* effect) {
		this->effects.push_back(effect);
	};

	double kineticEnergy() {
		return (this->velocity * this->velocity).magnitude() * .5 * this->mass;
	};

	double altitude() {
		return this->position.z;
	};

	void addForce(Vector3 const& force) {
		this->forces += force;
	};

	static Vector3 toLocalSpace(Vector3 vec) {
		
	};

	void update() {

		this->acceleration = this->forces / this->mass;
		this->position = this->velocity * this->dt + this->acceleration * 0.5 * (this->dt * this->dt);
		this->velocity = this->acceleration * this->dt;

		this->angularAcceleration = this->torque / this->angularMass;
		this->rotation = this->angularVelocity * this->dt + this->angularAcceleration * 0.5 * (this->dt * this->dt);
		this->angularVelocity = this->angularAcceleration * this->dt;

		this->torque = Vector3::zero();
		this->forces = Vector3::zero();
	};
};

class Effect {
public:

	Projectile* projectile;
	Logger* logger;

	Effect() {}

	virtual void update();
};

class Gravity : Effect {

public:

	Gravity(Projectile proj) {
		this->projectile = &proj;
		Logger log("Gravity Acceleration", &this->projectile->acceleration.y);
		this->logger = &log;
	};

	void update() {
		double alt = this->projectile->altitude();
		this->projectile->acceleration.y += G * pow((re / re + alt), 2.0);
		this->logger->update();
	};
};
