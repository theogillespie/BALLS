#pragma once

#include "Vector3.h"
#include "Constants.h"
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

	double magnitude() {
		return sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
	};

	Quaternion* normalize() {
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

		return Quaternion(this->w, x, y, z);
	}

	// fix euler to angle assignment (this prob needs to be done to toEuelrAngles as well) (w->x, y->z) but the math works!
	static Quaternion fromEuler(Vector3 const& eulerAngles) {
		double cosX = cos(eulerAngles.x / 2.0);
		double cosY = cos(eulerAngles.y / 2.0);
		double cosZ = cos(eulerAngles.z / 2.0);

		double sinX = sin(eulerAngles.x / 2.0);
		double sinY = sin(eulerAngles.y / 2.0);
		double sinZ = sin(eulerAngles.z / 2.0);

		double w = cosX * cosY * cosZ + sinX * sinY * sinZ;
		double x = cosX * cosY * sinZ - sinX * sinY * cosZ;
		double y = cosX * cosZ * sinY + sinX * sinZ * cosY;
		double z = cosY * cosZ * sinX - sinY * sinZ * cosX;

		return Quaternion(w, x, y, z);
	};

	Vector3 toEulerAngles() {
		Vector3 angles;

		double n1 = 2.0 * (this->w * this->x + this->y * this->z);
		double n2 = 1.0 - (2.0 * (this->x * this->x + this->y * this->y));
		double n3 = 2.0 * (this->w * this->y + this->x * -this->z);
		double n4 = 2.0 * (this->w * this->z + this->x * this->y);
		double n5 = 1.0 - (2.0 * (this->y * this->y + this->z * this->z));

		angles.x = atan2(n4, n5);
		if (abs(n3) >= 1.0) {
			angles.y = copysign(HALFPI, n3);
		}
		else {
			angles.y = asin(n3);
		}
		angles.z = atan2(n1, n2);

		return angles;
	}

	std::string toString() {
		char buffer[100];
		std::sprintf(buffer, "w: %f, x: %f, y: %f, z: %f", this->w, this->x, this->y, this->z);
		return buffer;
	};

	//awesome website:  https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm

	Quaternion operator + (Quaternion const& q) {
		double w = this->w + q.w;
		double x = this->x + q.x;
		double y = this->y + q.y;
		double z = this->z + q.z;

		return Quaternion(w, x, y, z);
	}

	Quaternion operator + (double const& n) {
		double w = this->w + n;
		double x = this->x + n;
		double y = this->y + n;
		double z = this->z + n;

		return  Quaternion(w, x, y, z);
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

		return  Quaternion(w, x, y, z);
	}

	Quaternion operator - (double const& n) {
		double w = this->w - n;
		double x = this->x - n;
		double y = this->y - n;
		double z = this->z - n;

		return  Quaternion(w, x, y, z);
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

		double w = this->w * q.w - this->x * q.x - this->y * q.y - this->z*q.z;
		double x = this->w * q.w + this->x * q.x + this->y * q.y - this->z * q.z;
		double y = this->w * q.w - this->x * q.x + this->y * q.y + this->z * q.z;
		double z = this->w * q.w + this->x * q.x - this->y * q.y + this->z * q.z;

		return Quaternion(w, x, y, z);
	}

	Quaternion operator * (double const& n) {
		double w = this->w * n;
		double x = this->x * n;
		double y = this->y * n;
		double z = this->z * n;

		return Quaternion(w, x, y, z);
	}
		
	Vector3 operator * (Vector3& a) { // removed const because cpp hates me
		Vector3 b(this->x, this->y, this->z);
		double w = this->w;

		return b * 2.0 * Vector3::dot(b, a) + (a * (w * w - Vector3::dot(b, b))) + b.cross(a) * w * 2.0;
	}

	Quaternion operator *= (Quaternion const& q) {
		this->w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
		this->x = this->w * q.w + this->x * q.x + this->y * q.y - this->z * q.z;
		this->y = this->w * q.w - this->x * q.x + this->y * q.y + this->z * q.z;
		this->z = this->w * q.w + this->x * q.x - this->y * q.y + this->z * q.z;
	}

	Quaternion operator *= (double const& n) {
		this->w *= n;
		this->x *= n;
		this->y *= n;
		this->z *= n;
	}

};