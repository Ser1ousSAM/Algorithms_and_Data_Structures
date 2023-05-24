#include <iostream>
#include <memory>
#include "Test.h"

using namespace std;
int main() 
{
	shared_ptr<Test> sp(new Test[3], default_delete<Test[]>());
	sp.get()[0].Val = 2;
	sp.get()[1].Val = 0;
	sp.get()[2].Val = 5;
	for (int i = 0; i < 3; i++) {
		cout << sp.get()[i].Val << endl;
	}
	unique_ptr<Test[]> p(new Test[3]);
	p[0].Val = 0;
	p[1].Val = 1;
	p[2].Val = 2;
	for (int i = 0; i < 3; i++) {
		cout << p[i].Val << endl;
	}
	cout << "--------" << endl;
	p.reset(new Test[2]);
	cout << "--------" << endl;
}