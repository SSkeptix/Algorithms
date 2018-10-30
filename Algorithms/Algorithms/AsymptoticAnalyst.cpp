#include "AsymptoticAnalyst.h"

void AsymptoticAnalyst::clear()
{
	_data.clear();
}

double AsymptoticAnalyst::checkFunc(double(*func)(ull a, ull b))
{
	double result = 0;

	for (unsigned i = 1; i < _data.size(); i++)
	{
		double a = _data[i].totalTime / _data[i - 1].totalTime;
		double b = func(_data[i].iterationCount, _data[i - 1].iterationCount);
		result = (0.5 * (i - 1) * result + a / b) / (0.5 * (i - 1) + 1);
	}
	return std::abs(result - 1);
}

void AsymptoticAnalyst::start()
{
	_startTime = std::chrono::system_clock::now();
}

void AsymptoticAnalyst::end()
{
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - _startTime;
	_data.back().totalTime = diff.count();
}

void AsymptoticAnalyst::measure(ull iterationCount, void(*func)())
{
	_data.push_back(TestData(iterationCount));
	start();
	func();
	end();
}

void AsymptoticAnalyst::measure(ull iterationCount, void(*func)(std::function<void()> start, std::function<void()> end))
{
	_data.push_back(TestData(iterationCount));
	func(std::bind(&AsymptoticAnalyst::start, this), std::bind(&AsymptoticAnalyst::end, this));
}

void AsymptoticAnalyst::getResult(std::ostream & out)
{
	std::sort(_data.begin(), _data.end(), [](TestData a, TestData b) { return a.iterationCount < b.iterationCount; });

	if (extendedResult)
		for (unsigned i = 0; i < _data.size(); i++)
			out << "Iterations: " << _data[i].iterationCount << ", time: " << _data[i].totalTime << " s" << std::endl;

	double errorRate = 0;

	errorRate = checkFunc([](ull a, ull b) { return (double)a / b; });
	out << "O(1) = " << errorRate * 100 << "%\n";
	errorRate = checkFunc([](ull a, ull b) { return (a * std::log2(a)) / (b * std::log2(b)); });
	out << "O(log(n)) = " << errorRate * 100 << "%\n";
	errorRate = checkFunc([](ull a, ull b) { return std::pow((double)a / b, 2); });
	out << "O(n) = " << errorRate * 100 << "%\n";
}

