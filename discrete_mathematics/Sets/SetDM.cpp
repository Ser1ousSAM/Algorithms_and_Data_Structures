#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <conio.h>

using namespace std;

set<string> U;

//Union
set<string> operator + (set<string> s1, set<string> s2) {
	set<string> res;
	for (auto i : s1)
		res.insert(i);
	for (auto i : s2)
		res.insert(i);
	return res;
}
//Intersection
set<string> operator * (set<string> s1, set<string> s2) {
	set<string> res;
	for (auto i : s1)
		if (s2.contains(i))
			res.insert(i);
	return res;
}
//Addition
set<string> operator ~ (set<string> s1) {
	set<string> res;
	for (auto i : U)
		if (!s1.contains(i))
			res.insert(i);
	return res;
}
//Difference
set<string> operator / (set<string> s1, set<string> s2) {
	set<string> res = s1;
	for (auto i : s1)
		if (s2.contains(i))
			res.erase(i);
	return res;
}
//Simmetric difference
set<string> operator || (set<string> s1, set<string> s2) {
	return (s1 / s2) + (s2 / s1);
}
bool operator == (set<string> s1, set<string> s2) {
	if (s1.size() != s2.size())
		return false;
	for (auto el : s1) {
		if (!s2.contains(el))
			return false;
	}
	return true;
}
bool operator != (set<string> s1, set<string> s2) {
	if (s1.size() != s2.size())
		return true;
	for (auto el : s1) {
		if (!s2.contains(el))
			return true;
	}
	return false;
}
int correctInput(int n) {
	while (true) {
		string temp;
		cin >> temp;
		n = atoi(temp.c_str());
		if (n == 0)
			cout << "Power of set must be natural integer" << '\n';
		else if (n > 0 && n <= 25)
			break;
		else
			cout << "Power of set must be from 1 to 25 elements(nums):" << '\n';
	}
	return n;
}

void display(set<string>& s, string name) {
	int count = 0;
	cout << "\n--------------------" << '\n';
	cout << "Size of set " << s.size() << '\n';
	cout << "Set " << name << '\n';
	for (const auto i : s) {
		count++;
		cout << i << "	";
		if (count % 2 == 0)
			cout << '\n';
	}
	cout << "\n--------------------" << '\n';
}

void showDependencies(set<string>& A, set<string>& B) {
	cout << "Dependencies between sets:\n";
	A == B ? cout << "A = B" : cout << "A != B";
	cout << "\n\n";
	A.size() == B.size() ? cout << "A equivalent to B" : cout << "A NOT equivalent to B";
	cout << "\n\n";
	if (A == B)
		cout << "A and B both subsets of each other";
	else {
		bool flag = true;
		if (A.size() == 0)
			cout << "A is empty and NOT a subset to B";
		else {
			for (auto el : A) {
				if (!B.contains(el))
					flag = false;
			}
			flag ? cout << "A is a subset to B" : cout << "A is NOT a subset to B";
		}
		cout << "\n\n";

		if (B.size() == 0)
			cout << "A is empty and NOT a subset to B";
		else {
			flag = true;
			for (auto el : B) {
				if (!A.contains(el))
					flag = false;
			}
			flag ? cout << "B is a subset to A" : cout << "B is NOT a subset to A";
		}
	}
	cout << "\n\n";
}

void AddFromU(set<string>& s) {
	char input = 0;
	int numberOfEl = 0;
	vector<string> elems;
	for (auto i : U)
		elems.push_back(i);
	int sizeOfElems = elems.size();
	string temp;

	cout << "Press Tab to switch elements and choose by Enter. Press an Q to stop filling set\n";
	while (s.size() < U.size()) {
		input = _getch();
		if (input == '\t')
			numberOfEl++;
		else if ((int)input == int('Q') || (int)input == int('q') || (int)input == int('й') || (int)input == int('Й'))
			break;
		cout << "\r                                                                                                    \r";
		if (numberOfEl == sizeOfElems)
			numberOfEl %= sizeOfElems;
		temp = elems[numberOfEl];
		cout << temp;
		if (input == '\r') {
			cout << '\n';
			s.insert(elems[numberOfEl]);
			elems.erase(elems.begin() + numberOfEl);
			sizeOfElems--;
			if (numberOfEl != 0)
				numberOfEl--;
			cout << "Current power of set = " << s.size() << "\n";
		}
	}
}
int main() {
	cout << "KHARITONOV GLEB 2012 GROUP\n";
	cout << "Enter a power of U universum (including 25 lines):" << '\n';
	int n = 0;
	n = correctInput(n);
	cout << "Power of U = " << n << '\n';
	cout << "Fill an universum:" << '\n';
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ")";
		string temp;
		cin >> temp;
		U.insert(temp);
	}
	n = U.size();
	cout << "Power of U = " << n << '\n';

	cout << "Fill set A" << '\n';
	set<string> A;
	AddFromU(A);
	display(A, "set A");

	cout << "Fill set B" << '\n';
	set<string> B;
	AddFromU(B);
	display(B, "set B");
	showDependencies(A, B);

	set<string> C = A + B, D = A * B, E = A / B, F = A || B, G = ~A, H = ~B;
	cout << "\n";
	display(A, "set A");
	display(B, "set B");
	display(C, "Union A, B");
	display(D, "Intersection A, B");
	display(E, "Difference A / B");
	display(F, "Simmetric difference or Union (A / B), (B / A)");
	display(G, "Addition U / A");
	display(H, "Addition U / B");
	while (true) {
		cout << "Press Q to end\n";
		char input = _getch();
		if ((int)input == int('Q') || (int)input == int('q') || (int)input == int('й') || (int)input == int('Й'))
			exit(EXIT_SUCCESS);
	}
}
