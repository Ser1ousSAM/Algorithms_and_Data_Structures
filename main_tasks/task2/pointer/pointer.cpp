#include<iostream>
#include "utils.h"

using std::cout;
using std::cin;
typedef unsigned char byte;


int main() {
    int x = 3;
    int *p = &x;
    cout << x << ' ' << *p << ' ' << p << '\n';

    p++;
    cout << p << '\n';

    cout << &p << '\n';

    cout << p - &x << '\n';
    //using byte = unsigned char;
    byte *pb = (byte *) --p;
    // вернули указатель на x и преобразовали
    for (byte *pt = pb; pt - pb < sizeof(int); pt++)
        cout << (int) *pt << ' '; // выводим как int
    cout << '\n';
    int a = 2, b = 5;

    cout << a << " " << b << '\n';
    utils::Swap(a, b);
    cout << a << " "<< b << '\n';

    utils::Swap(&a, &b);
    cout << a<< " " << b << '\n';

    int nm = 8;
    int* num = &nm;
    cout << num << '\n' << *num << '\n' << &(*num) << '\n';

    return 0;
}

