#include <iostream>
#include <cstring>
#include "Wagner_Fischer.h"

int Distance(const char* s, const char* t) {
	int m = std::strlen(s);
	int n = std::strlen(t);
	int* p1 = new int[n];
	int* p2 = new int[n];
	for (int i = 0; i < n; i++) {
		p1[i] = i;
	}
	for (int j = 0; j < m; j++) {
		p2[0] = j + 1;
		for (int i = 0; i < n-1; i++) {
			int cost = (s[i] == t[j]) ? 0 : 1;
			p2[i + 1] = std::min(std::min(p2[i] + 1, p1[i + 1] + 1), p1[i] + cost);
		}
		std::swap(p1, p2);
	}
	int res = p2[n - 1];
	delete[] p1;
	delete[] p2;
	return res;
}

int main()
{
	const char* s = "qwert";
	const char* t = "qw";
	WF A;
	A.Init(s, t);
	for (int i = 0; i < A.Rows(); i++) {
		for (int j = 0; j < A.Columns(); j++) {
			std::cout << A.Get(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << A.Distance() << std::endl;
	std::cout << Distance(s, t) << std::endl;
}

