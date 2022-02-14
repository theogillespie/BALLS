#pragma once

#include "Quaternion.h"
#include "core.h"
#include "../io/io.h"
#include "../solvers/solvers.h"

#include <cstdint>
#include <vector>
#include <cmath>
#include <string>

class Effect;

struct ProjectileDimensions {
	double rifilingTwist = 1; // rifiling twist (in/turn)
	double caliber = .44; // caliber (inches)
	double length = 1; // inch
	double mass = 1; // grains!!!!
	double i = length / mass;
};

class Projectile {
public:

	string name;
	ProjectileDimensions dimensions;

	Vector3 acceleration;

	Vector3 initialPosition;
	Vector3 initialVelocity;

	Vector3 position;
	Vector3 velocity;
	Vector3 forces;
	Vector3 constantForces;

	Vector3 eulerAngles;
	Quaternion rotation;
	Vector3 angularVelocity;
	Vector3 angularAcceleration;
	Vector3 torque;
	Vector3 momentOfInertia;

	Vector3 oldCoriolis;
	Vector3 oldSpinDrift;

	Curve drag;

	double dt;
	double elaspedTime;
	double gravity;
	double mass;
	double direction;
	
	
	Projectile(double mass, double dt=0.001, Vector3 const& initPosition=Vector3::zero()) {
		this->initialPosition = initPosition;
		this->position = this->initialPosition;
		this->dt = dt;
		this->mass = mass;
		
		this->momentOfInertia = Vector3(0, 0, 0);
	};

	Projectile() {};

	~Projectile() {};

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


	double kineticEnergy() {
		return (this->velocity * this->velocity).magnitude() * .5 * this->mass;
	};

	double altitude() {
		if (this->position.z > MAXALT) {
			Console::error("WARNING: Projectiles Altitude exceeds supported limit (" + to_string(MAXALT) + "m), results may be inaccurate");
		}
		return this->position.z;
	};

	double speed() {
		return this->velocity.magnitude();
	};

	double getMach() {
		return this->speed() / Atmosphere::machAtAltitude(this->altitude());
	}

	void addForce(Vector3 const& force) {
		this->forces += force;
	};

	// accounts for rotation
	void addRelativeForce(Vector3 const& force) {
		this->forces += this->toLocalSpace(force);
	}

	void addConstantForce(Vector3 const& force) {
		this->constantForces += force;
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

	void applyGravity() {
		if(this->altitude() <= 0) {
			this->acceleration.y += -G;
		}
		else {
			this->acceleration.y += -(G * pow((re / re + this->altitude()), 2.0));
		}
	}

	void applyDrag() {

	}

	void applyCoriolis() {
		double distance = Vector3::distance(this->initialPosition, this->position);
		double projectileDrop = this->initialPosition.y - this->position.y;

		double xDeflection = (OMEGA * (distance * distance) * sin(LAT)) / this->speed();
		double yDeflection = (1 - 2 * (OMEGA * this->initialPosition.magnitude() / this->gravity) * cos(LAT) * sin(direction));
		yDeflection = (yDeflection * projectileDrop) - projectileDrop;

		Vector3 current = Vector3(xDeflection, yDeflection, 0);
		current -= this->oldCoriolis;
		this->oldCoriolis = current;
		
		this->position += current;
	}

	void applyEoetvoes() {
		double centripedalAccel = 2 * OMEGA * (this->initialVelocity.magnitude() / this->gravity) * cos(LAT) * sin(this->direction);
		this->acceleration += Vector3(0, -centripedalAccel, 0);
	};

	double calculateGyroStability() {
		double p = Atmosphere::densityAtAltitude(this->altitude()) / 3.954;
		double p1 = (8 * PI) / (p * pow(this->dimensions.rifilingTwist, 2) * pow(this->dimensions.caliber, 5) * .57 * this->dimensions.i);
		double p2 = (this->dimensions.mass * pow(this->dimensions.caliber, 2)) / (4.83 * (1 + pow(this->dimensions.i, 2)));
		return p1 * p2;
	};

	void applySpinDrift() {
		double drift = 1.25 * (calculateGyroStability() + 1.2) * pow(this->elaspedTime, 1.83);
		Vector3 spinDrift = Vector3(drift, 0, 0);
		spinDrift -= this->oldSpinDrift;
		this->oldSpinDrift = spinDrift;
		this->position += spinDrift;
	}

	void update() {
		this->elaspedTime += dt;
		this->forces += this->constantForces;

		this->acceleration = this->forces / this->mass;
		this->applyGravity();

		this->position += this->velocity * this->dt + this->acceleration * 0.5 * (this->dt * this->dt);
		this->velocity += this->acceleration * this->dt;

		//this->applyCoriolis(); // causes -nan(ind) wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwooooooooooooooooooo
		//this->applyEoetvoes();
		//this->applySpinDrift();

		this->angularAcceleration = this->torque / this->momentOfInertia;
		this->angularVelocity = this->angularAcceleration * this->dt;
		float angularVelocityMagnitude = this->angularVelocity.magnitude();
		this->rotation *= Quaternion::fromAxisAngle(this->angularVelocity / angularVelocityMagnitude, angularVelocityMagnitude * this->dt);
		
		this->eulerAngles = this->rotation.toEulerAngles();
		this->direction = atan2(this->velocity.z, this->velocity.x);

		this->torque = Vector3(0,0,0);
		this->forces = Vector3(0,0,0);
		this->acceleration = Vector3(0, 0, 0);
	};
};


