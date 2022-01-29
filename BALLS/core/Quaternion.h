#pragma once

#include "Vector3.h"

class Quaternion {
public: 

	double w, x, y, z;

	Quaternion(double _w, double _x, double _y, double _z) {
		this->w = _w;
		this->x = _x;
		this->y = _y;
		this->z = _z;
	};

	Quaternion(Vector3 const& eulerAngles) {
		this = Quaternion.fromEuler(eulerAngles);
	};

	Vector3 toEulerAngles() {};

	static Quaternion fromEuler(Vector3 const& eulerAngles) {};
};