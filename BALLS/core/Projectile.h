#pragma once

#include<vector>

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btTransformUtil.h"

#include "Misc.h"
#include "Effects.h

using namespace std;


class Projectile {

public:

	vector<Effect> effects;
	btRigidbody rb;

	Projectile(double mass, btVector3 dimensions, btVector3 position=btVector3(0,0,0)) {

		btEmptyShape* shape = new btEmptyShape();

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(vecZero());

		btVector3 localIntertia = vecZero();
		btDefaultMotionState* state = new btDefaultMotionState(transform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, state, shape, localInertia);

		rb = new btRigidbody(cInfo);
	}

	~Projectile() {}

	void addEffect(Effect effect) {
		effects.push_back(effect);
	}

	void update() {
		for (byte i = 0; i < effects.size(); i++) {
			effects[i].update();
		}
	}
};