#include<vector>


using namespace std;

// one dimension logging class
class Logger() {
private:
	double* value;
	vector<double> logs;

public:
	Logger(double* number) {
		value = number;
	};

	void update() {
		logs.push_back(getValue());
	};

	double getValue() {
		return &value;
	}

	double[] getData() {
		double arr[logs.size()];
		std::copy(logs.begin(), logs.end(), logs);
		return arr;
	}
}