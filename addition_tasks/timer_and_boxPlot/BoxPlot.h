#pragma once
#include <vector>
#include <algorithm> 

class BoxPlot
{
public:
	inline static double min(std::vector<double> x) {
		double q1 = lq(x);
		double q3 = uq(x);
		return q1 - 1.5 * (q3 - q1);
	}
	static double lq(std::vector<double> x) {
		std::sort(x.begin(), x.end());
		size_t s = x.size();
		double q1;
		if (s % 2 == 0) {
			std::vector<double> vec(s / 2);
			std::copy(x.begin(), x.begin() + s / 2 + 1, vec.begin());
			q1 = median(vec);
		}
		else {
			std::vector<double> vec((s - 1) / 2);
			std::copy(x.begin(), x.begin() + (s - 1) / 2, vec.begin());
			q1 = median(vec);
		}
		return q1;
	}
	static double median(std::vector<double> x) {
		std::sort(x.begin(), x.end());
		size_t s = x.size();
		if (s % 2 == 0) {
			return (x[s / 2 - 1] + x[s / 2]) / 2;
		}
		return x[(s-1) / 2];
	}
	static double mean(std::vector<double> x) {
		double sum = 0;
		for (double i : x) {
			sum += i;
		}
		return sum / x.size();
	}
	static double stddev(std::vector<double> x) {
		double d = mean(x);
		double sum = 0;
		for (double i : x) {
			sum += (i-d)*(i-d);
		}
		return std::sqrt(sum / x.size());
	}
	static double uq(std::vector<double> x) {
		std::sort(x.begin(), x.end());
		size_t s = x.size();
		double q3;
		if (s % 2 == 0) {
			std::vector<double> vec(s / 2);
			std::copy(x.begin() + s / 2 + 1, x.end(), vec.begin());
			q3 = median(vec);
		}
		else {
			std::vector<double> vec((s - 1) / 2);
			std::copy(x.begin() + (s - 1) / 2 + 1, x.end(), vec.begin());
			q3 = median(vec);
		}
		return q3;
	}
	static double max(std::vector<double> x) {
		double q1 = lq(x);
		double q3 = uq(x);
		return q3 + 1.5 * (q3 - q1);
	}
	static std::vector<double> out(std::vector<double> x) {
		std::vector<double> vec;
		double q1 = min(x);
		double q3 = max(x);
		for (double i : x) {
			if (i<q1 || i>q3) {
				vec.push_back(i);
			}
		}
		return vec;
	}
};
