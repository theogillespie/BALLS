#pragma once

#include "Vector3.h"

#include<vector>
#include<string>

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

	std::string name;

	Logger(std::string loggerName, double* number) {
		this->name = loggerName;
		this->scalarValue = number;
		this->mode = SCALAR;
	};

	Logger(std::string loggerName, Vector3* vec) {
		this->name = loggerName;
		this->vectorValue = vec;
		this->mode = VECTOR;
	};

	~Logger() {
		this->scalarLogs.clear();
		this->vectorLogs.clear();
	};

	void update() {
		switch (this->mode) {
			case SCALAR:
				this->scalarLogs.push_back(*this->scalarValue);
				break;
			
			case VECTOR:
				this->vectorLogs.push_back(*this->vectorValue);
				break;
		}
	};

	std::vector<double> getData(LOGMODE type=SCALAR) { // kinda hacky but ok
		return this->scalarLogs;
	};

	std::vector<Vector3> getData() {
		return this->vectorLogs;
	};
}