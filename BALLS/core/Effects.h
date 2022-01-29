#pragma once

#include<Projectile.h>
#include<string>

using namespace std;

struct EffectProperties  {
	string name = "Effect";
}

class Effect {
private:
	Projectile* projectile;

public:

	EffectProperties props;

	Effect(Projectile* pro, EffectProperties prop = EffectProperties) {
		projectile = pro;
	}

	virtual void update();

};