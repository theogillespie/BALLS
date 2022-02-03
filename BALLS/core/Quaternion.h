#pragma once

#include "Vector3.h"
#include "Constants.h"

#include <cmath>
#include <sstream>
#include <string>

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

	// https://github.com/peregrine-developments/Orientation/blob/master/Quaternion/Quaternion.cpp
	static Quaternion fromEuler(Vector3 eulerAngles) {
		eulerAngles.toRad();
		double cy = cos(eulerAngles.z / 2);
		double cp = cos(eulerAngles.y / 2);
		double cr = cos(eulerAngles.x / 2);

		double sy = sin(eulerAngles.z / 2);
		double sp = sin(eulerAngles.y / 2);
		double sr = sin(eulerAngles.x / 2);

		double w = cr * cp * cy + sr * sp * sy;
		double x = sr * cp * cy - cr * sp * sy;
		double y = cr * sp * cy + sr * cp * sy;
		double z = cr * cp * sy - sr * sp * cy;

		return Quaternion(w, x, y, z);
	};

	
	Vector3 toEulerAngles() {
		Vector3 ang;

		double sinr_cosp = 2 * (this->w * this->x + this->y * this->z);
		double cosr_cosp = 1 - (2 * (this->x * this->x + this->y * this->y));
		ang.x = atan2(sinr_cosp, cosr_cosp);

		double sinp = 2 * (this->w * this->y + -this->z * this->x);
		if (abs(sinp) >= 1) {
			ang.y = copysign(HALFPI, sinp); // return 90 if out of range
		}
		else {
			ang.y = asin(sinp);
		}

		double siny_cosp = 2 * (this->w * this->z + this->x * this->y);
		double cosy_cosp = 1 - (2 * (this->y * this->y + this->z * this->z));
		ang.z = atan2(siny_cosp, cosy_cosp);

		ang.toDeg();
		return ang;
	}

	std::string toString() {
		std::ostringstream os;
		os << "w: " << this->w << ", x: " << this->x << ", y : " << this->y << ", z : " << this->z;
		return os.str();
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