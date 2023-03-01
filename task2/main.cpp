#include<iostream>

using namespace std;

int main(){
    int x = 3;
    int *p = &x;
    cout << x << ' ' << *p << ' ' << p << '\n';
    
    p++;
    cout << p << '\n';

    cout << &p << '\n';

    cout << p-&x << '\n';

    return 0;
}