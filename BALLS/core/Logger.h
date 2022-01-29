#pragma once

#include "Vector3.h"

#include<vector>

enum LOGMODE : uint8_t {
	SCALAR = 0,
	VECTOR = 1
};

// one dimension logging class
class Logger {
private:

	LOGMODE mode;

	double* scalarValue;
	Vector3* vectorValue;

	std::vector<double> scalarLogs;
	std::vector<Vector3> vectorLogs;

public:

	Logger(double* number) {
		this->scalarValue = number;
		this->mode = LOGMODE.SCALAR;
	};

	Logger(Vector3* vec) {
		this->vectorValue = vec;
		this->mode = LOGMODE.VECTOR;
	};

	~Logger() {
		this->scalarLogs.clear();
		this->vectorLogs.clear();
	};

	void update() {
		switch (this->mode) {
			case LOGMODE.SCALAR:
				this->scalarLogs.push_back(&this->scalarValue);
				break;
			
			case LOGMODE.VECTOR:
				this->vectorLogs.push_back(&this->vectorValue);
				break;
		}
	};

	double[] getData() {
		double arr[this->scalarLogs.size()];
		std::copy(this->scalarLogs.begin(), this->scalarLogs.end(), this.scalarLogs);
		return arr;
	};

	Vector3[] getData() {
		Vector3 arr[this->vectorLogs.size()];
		std::copy(this->vectorLogs.begin(), this->vectorLogs.end(), this.vectorLogs);
		return arr;
	}
}