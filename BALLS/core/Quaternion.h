#pragma once

#include "Vector3.h"
#include <cmath>

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

	double magnitude() {
		return sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
	};

	Quaternion normalize() {
		double m = this->magnitude();

		this->w /= m;
		this->x /= m;
		this->y /= m;
		this->z /= m;

		return this;
	};

	Quaternion conjugate() {
		double x = -this->x;
		double y = -this->y;
		double z = -this->z;

		return new Quaternion(this->w, x, y, z);
	}

	static Quaternion fromEuler(Vector3 const& eulerAngles) {
		double cosX = cos(x / 2.0);
		double cosY = cos(y / 2.0);
		double cosZ = cos(z / 2.0);

		double sinX = sin(x / 2.0);
		double sinY = sin(y / 2.0);
		double sinZ = sin(z / 2.0);

		double w = cosX * cosY * cosZ + sinX * sinY * sinZ;
		double x = cosX * cosY * sinZ - sinX * sinY * cosZ;
		double y = cosX * cosZ * sinY + sinX * sinZ * cosY;
		double z = cosY * cosZ * sinX - sinY * sinZ * cosX;

		return Quaternion(w, x, y, z);
	};

	Vector3 toEulerAngles() {
		return NULL;
	}

	//awesome website:  https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm

	Quaternion operator + (Quaternion const& q) {
		double w = this->w + q.w;
		double x = this->x + q.x;
		double y = this->y + q.y;
		double z = this->z + q.z;

		return new Quaternion(w, x, y, z);
	}

	Quaternion operator + (double const& n) {
		double w = this->w + n;
		double x = this->x + n;
		double y = this->y + n;
		double z = this->z + n;

		return new Quaternion(w, x, y, z);
	}

	Quaternion operator += (Quaternion const& q) {
		this->w += q.w;
		this->x += q.x;
		this->y += q.y;
		this->z += q.z;
	}

	Quaternion operator += (double const& n) {
		this->w += n;
		this->x += n;
		this->y += n;
		this->z += n;
	}

	Quaternion operator - (Quaternion const& q) {
		double w = this->w - q.w;
		double x = this->x - q.x;
		double y = this->y - q.y;
		double z = this->z - q.z;

		return new Quaternion(w, x, y, z);
	}

	Quaternion operator - (double const& n) {
		double w = this->w - n;
		double x = this->x - n;
		double y = this->y - n;
		double z = this->z - n;

		return new Quaternion(w, x, y, z);
	}

	Quaternion operator -= (Quaternion const& q) {
		this->w -= q.w;
		this->x -= q.x;
		this->y -= q.y;
		this->z -= q.z;
	}

	Quaternion operator -= (double const& n) {
		this->w -= n;
		this->x -= n;
		this->y -= n;
		this->z -= n;
	}

	Quaternion operator * (Quaternion const& q) {
		double w = this->w * q.a - this->x * q.x - this->y * q.y - this->z*q.z;
		double x = this->w * q.a + this->x * q.x + this->y * q.y - this->z * q.z;
		double y = this->w * q.a - this->x * q.x + this->y * q.y + this->z * q.z;
		double z = this->w * q.a + this->x * q.x - this->y * q.y + this->z * q.z;

		return new Quaternion(w, x, y, z);
	}

	Quaternion operator * (double const& n) {
		double w = this->w * n;
		double x = this->x * n;
		double y = this->y * n;
		double z = this->z * n;

		return new Quaternion(w, x, y, z);
	}

	Quaternion operator *= (Quaternion const& q) {
		this->w = this->w * q.a - this->x * q.x - this->y * q.y - this->z * q.z;
		this->x = this->w * q.a + this->x * q.x + this->y * q.y - this->z * q.z;
		this->y = this->w * q.a - this->x * q.x + this->y * q.y + this->z * q.z;
		this->z = this->w * q.a + this->x * q.x - this->y * q.y + this->z * q.z;
	}

	Quaternion operator *= (double const& n) {
		this->w *= n;
		this->x *= n;
		this->y *= n;
		this->z *= n;
	}

};