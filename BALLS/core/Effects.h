#pragma once

#include "core.h"
#include "../solvers/solvers.h"

class DragSolver;

class Effect {
public:

	Projectile* projectile;
	Logger* logger;

	Effect(Projectile* proj) {
		this->projectile = proj;
	};

    virtual void preload(); // where things like drag curve generation begin

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

class Drag : Effect {
    public: 
        Curve dragCurve;
        DragSolver* dragSolver;

        Drag(Projectile* proj, DragSolver* solver): Effect(proj) {
            this->logger = new Logger("Drag Force", &this->projectile->position);
            this->dragSolver = solver;
        };

        void preload() override {
            Console::print("Generating Drag Curve...");
            this->dragCurve = this->dragSolver->generateCurve();
        };

        void update() override {
            double dragForce = this->dragCurve.getValue(this->projectile->speed());
            this->projectile->addRelativeForce(Vector3(1, 0, 0) * dragForce);
        };
};
