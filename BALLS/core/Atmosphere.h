#pragma once

#include "Constants.h"
#include "Vector3.h"

#include <cmath>
#include <random>

using namespace std;

#define MAXALT 86000

// works up to ~86 KM
class Atmosphere {
private:
	//two parameter weibull
	static double windDistribution(double a=2.0, double b=10.0) {
		double x = rand() % 10 + 1;
		return (a / b) * pow(x / b, a - 1.0) * exp(pow(-(x / b), a));
	}

public:

	static Vector3 generateWind(double maxSpeed) {

		double const x = Atmosphere::windDistribution(2.0, maxSpeed);
		double const y = Atmosphere::windDistribution(2.0, maxSpeed);
		return Vector3(x, y, 0.0);
	}

	static double pressureAtAltitude(double alt) {
		//Accounts for stratosphere's constant temp
		if (alt >= 11000 && alt <= 20000) {
			return Pb * exp((-G * M * (alt-h) / (R * Tb)));
		}

		return Pb * pow((Tb + Lb * (alt - h)) / Tb, (-G * M) / (R * Lb));
	}

	static double densityAtAltitude(double alt) {
		return Pb * pow(Tb / (Tb + Lb * (alt-h)), 1 + ((G * M) / (R * Lb)));
	}
};