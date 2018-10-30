#pragma once
#include <numeric>
#include <chrono>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

typedef unsigned long long ull;
static bool extendedResult = true;

class AsymptoticAnalyst {
public:
	void clear();
	void measure(ull iterationCount, void(*func)());
	void measure(ull iterationCount, void(*func)(std::function<void()> start, std::function<void()> end));

	void getResult(std::ostream& out);
private:
	std::chrono::time_point<std::chrono::system_clock> _startTime;
	double checkFunc(double(*func)(ull a, ull b));

	void start();
	void end();

	struct TestData {
		ull iterationCount;
		double totalTime;
		TestData() { }
		TestData(ull iterationCount) : iterationCount(iterationCount) { }
	};

	std::vector<TestData> _data;
};