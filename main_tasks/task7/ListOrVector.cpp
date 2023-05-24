#include <iostream>
#include <list>
#include <vector>
#include <chrono>

using namespace std;
int main()
{
    int n = 2000, m = 200;
    list<int> l;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        l.push_back(i);
        v.push_back(i);
    }
    int c = 0;
    /*int k = 0;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < m; i++) {
        k++;
        l.push_back(k);
        l.pop_back();
        k++;
    }
    auto stop = chrono::steady_clock::now();
    auto dt = chrono::duration_cast<chrono::microseconds>(stop - start).count();*/
    

    int k = 0;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < m; i++) {
        k++;
        v.insert(v.begin(),k);
        v.erase(v.begin());
        k++;
    }
    auto stop = chrono::steady_clock::now();
    auto dt = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    cout << dt;
}
