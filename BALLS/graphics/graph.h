#pragma once


#include "matplotlibcpp.h"

#include<vector>
#include<string>

using namespace std;

class Graphing {

	static void lineChart(vector<double> x, vector<double> y, string filename) {
		plt::plot(x, y);
		plt::save(filename);
	}
};
