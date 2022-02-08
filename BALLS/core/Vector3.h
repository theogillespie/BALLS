#pragma once

#include"Constants.h"

#include <cmath>

#include <string>
#include<sstream>

class Vector3 {
public:
	double x, y, z;
	Vector3(double _x, double _y, double _z) {
		this->x = _x;
		this->y = _y;
		this->z = _z;
	};

	Vector3(double _x, double _y) {
		this->x = _x;
		this->y = _y;
	};

	Vector3(double _x) {
		this->x = _x;
	};

	Vector3() {};

	~Vector3() {};

	static Vector3 zero() {
		return Vector3(0, 0, 0);
	};

	Vector3 normal() {
		double const m = this->magnitude();
		return Vector3(this->x / m, this->y / m, this->x / m);
	};

	double magnitude() {
		return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	};

	Vector3 endPosition() {
		return (Vector3(this->x, this->y, this->z) * this->magnitude());
	};

	Vector3* invert() {
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		return this;
	};

	Vector3* toRad() {
		this->x *= DEGTORAD;
		this->y *= DEGTORAD;
		this->z *= DEGTORAD;
		return this;
	}

	Vector3* toDeg() {
		this->x *= RADTODEG;
		this->y *= RADTODEG;
		this->z *= RADTODEG;
		return this;
	}

	std::string toString() {
		std::ostringstream os;
		os << "x: " << this->x << ", y: " << this->y << ", z: " << this->z;
		return os.str();
	};

	static double dot(Vector3 const& a, Vector3 const& b) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	};

	Vector3 cross(Vector3 const& vec) {
		double x = this->y * vec.z - this->z * vec.y;
		double y = this->z * vec.x - this->x * vec.z;
		double z = this->x * vec.y - this->x * vec.x;

		return Vector3(x, y, z);
	};
	 
	static double distance(Vector3 const& a, Vector3 const& b) {
		return sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0) + pow(b.z - a.z, 2.0));
	};

	Vector3 operator + (Vector3 const& vec) {
		return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	};

	Vector3 operator + (double const& n) {
		return Vector3(this->x + n, this->y + n, this->z + n);
	};

	Vector3& operator += (Vector3 const& vec) {
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
	};

	Vector3 operator += (double const& n) {
		this->x += n;
		this->y += n;
		this->z += n;
	};

	Vector3 operator - (Vector3 const& vec) {
		return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	};

	Vector3 operator - (double const& n) {
		return Vector3(this->x - n, this->y - n, this->z - n);
	};

	Vector3 operator -= (Vector3 const& vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
	};

	Vector3 operator -= (double const& n) {
		this->x -= n;
		this->y -= n;
		this->z -= n;
	};

	Vector3 operator * (Vector3 const& vec) {
		return Vector3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	};

	Vector3 operator * (double const& n) {
		return Vector3(this->x * n, this->y * n, this->z * n);
	};


	Vector3 operator *= (Vector3 const& vec) {
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
	};

	Vector3 operator *= (double const& n) {
		this->x *= n;
		this->y *= n;
		this->z *= n;
	};

	Vector3 operator / (Vector3 const& vec) {
		return Vector3(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	};

	Vector3 operator / (double const& n) {
		return Vector3(this->x / n, this->y / n, this->z / n);
	};

}; 
