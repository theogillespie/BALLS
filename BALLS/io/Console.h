#pragma once

#include <string>
#include <iostream>

using namespace std;

#define COLOR_WHITE "\u001b[37m"
#define COLOR_YELLOW "\u001b[33m"
#define COLOR_RED "\u001b[31m"

class Console {
public:
	static void print(string msg) {
		cout << COLOR_WHITE << msg << endl;
	}
	static void warn(string msg) {
		cout << COLOR_YELLOW << "WARNING: " << msg << endl;
	}
	static void error(string msg) {
		cout << COLOR_RED << "ERROR: " << msg << endl;
	}
};
