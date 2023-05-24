// KMP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KMP_StateMachine.h"
#include <fstream>

int main()
{
	KMP_StateMachine* sm = new KMP_StateMachine("vCode", 5);
	string s = "akjndakjnvCodeKNnksamdjuwen";
	for (char i : s) {
		sm->Accept(i);
		if (sm->IsFinal()) {
			cout <<" infected" << endl;
			break;
		}
	}
	/*char fname[] = "TestData/i3.tst";
	std::ifstream ifs(fname, std::ios::binary);
	if (ifs.is_open()) {
		char ch;
		int i = 1;
		while (ifs.get(ch)) {
			sm->Accept(ch);
			if (sm->IsFinal()) {
				i = 0;
				break;
			}
		}
		cout << endl;
		if (i == 0) {
			cout << fname << " infected" << endl;
		}
		else {
			cout << fname << " healthy" << endl;
		}
	}
	else {
		std::cout << fname << " not found!" << std::endl;
	}*/
	delete sm;

	return 0;
}

