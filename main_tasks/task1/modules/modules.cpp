#include <iostream>
#include "utils.h"
using namespace std;

int main()
{
	int x = 3, y = 5;
	cout << x + y << '\n';
	cout << utils::Plus(x, y);
}