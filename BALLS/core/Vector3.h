#pragma once

#include <cmath>

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

	~Vector3() {}

	static zero() {
		return new Vector3(0, 0, 0);
	};

	Vector3 normal() {
		double const m = this->magnitude();
		return new Vector3(this->x / m, this->y / m, this->x / m);
	};

	double magnitude() {
		return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	};

	void normal() {
		this.x = -this.x;
		this.y = -this.y;
		this.z = -this.z;
	};

	char[] toString() {
		char buffer[50];
		sprintf(buffer, "x: %f.4, y: %f.4, z: %f.4", v->getX(), v->getY(), v->getZ());
		return buffer;
	};

	static double dot(Vector3 const& a, Vector3 const& b) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	};

	static double distance(Vector3 const& a, Vector3 const& b) {
		return sqrt(pow(this.b.x - this.a.x, 2.0) + pow(this.b.y - this.a.y, 2.0) + pow(this.b.z - this.a.z, 2.0));
	}

	Vector3 operator + (Vector3 const& vec) {
		return new Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	};

	Vector3 operator + (double const& n) {
		return new Vector3(this->x + n, this->y + n, this->z + n);
	};

	Vector3 operator += (Vector3 const& vec) {
		this.x += vec.x;
		this.y += vec.y;
		this.z += vec.z;
	};

	Vector3 operator += (double const& n) {
		this.x += n;
		this.y += n;
		this.z += n;
	};

	Vector3 operator - (Vector3 const& vec) {
		return new Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	};

	Vector3 operator - (double const& n) {
		return new Vector3(this->x - n, this->y - n, this->z - n);
	};

	Vector3 operator -= (Vector3 const& vec) {
		this.x -= vec.x;
		this.y -= vec.y;
		this.z -= vec.z;
	};

	Vector3 operator -= (double const& n) {
		this.x -= n;
		this.y -= n;
		this.z -= n;
	};

	Vector3 operator * (Vector3 const& vec) {
		return new Vector3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	};

	Vector3 operator * (double const& n) {
		return new Vector3(this->x * n, this->y * n, this->z * n);
	};

	Vector3 operator *= (Vector3 const& vec) {
		this.x *= vec.x;
		this.y *= vec.y;
		this.z *= vec.z;
	};

	Vector3 operator *= (double const& n) {
		this.x *= n;
		this.y *= n;
		this.z *= n;
	};

	Vector3 operator / (Vector3 const& vec) {
		return new Vector3(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	};

	Vector3 operator / (double const& n) {
		return new Vector3(this->x / n, this->y / n, this->z / n);
	};

}; 