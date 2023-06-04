#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include "Timer.h"

using namespace std;

vector<int> fib;
const int l = 10;

string f_code(char ch)
{
    string s = "";
    int ost = (int)ch;
    int k = 0;
    for (int i = 0; i < l; i++) {
        if (ost < fib[i + 1]) {
            k = i;
            break;
        }
    }
    for (int i = k; i >= 0; i--) {
        if (ost >= fib[i]) {
            ost -= fib[i];
            s += "1";
        }
        else {
            s += "0";
        }
    }
    for (int i = 0; i < l - k; i++) {
        s = "0" + s;
    }
    s += "1";
    return s;
}

char f_decode(string s)
{
    int out = 0;
    for (int i = 0; i < l; i++) {
        if (s[l - i] == '1') {
            out += fib[i];
        }
    }
    return (char)out;
}

int main(int argc, char* argv[]) {
    Timer<double>::reset();
    int f = 1;
    fib.push_back(1);
    fib.push_back(2);
    for (int i = 1; i < l; i++) {
        fib.push_back(fib[i] + fib[i - 1]);
    }

    if (argc < 3) {
        cout << "Enter command" << endl;
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        string inp;
        std::ifstream fIn(argv[2], std::ios::binary);
        if (!fIn.is_open())
        {
            cout << "Can not open file" << argv[2] << endl;
            return 0;
        }
        inp.append((istreambuf_iterator<char>(fIn)), istreambuf_iterator<char>());
        fIn.close();
        std::ofstream fOut(argv[3], std::ios::binary);
        if (!fOut.is_open())
        {
            cout << "Can not open file" << argv[3] << endl;
            return 0;
        }
        for (const auto& ch : inp) {
            string z = f_code(ch);
            fOut << z;
        }
        fOut.close();
        cout << "Compressed"<<endl;
        cout << Timer<double>::elapsed_milliseconds() << " milliseconds" << endl;
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0) {

        string inp;
        std::ifstream fIn(argv[2], std::ios::binary);
        if (!fIn.is_open())
        {
            cout << "Can not open file "<< argv[2] << endl;
            return 0;
        }
        inp.append((istreambuf_iterator<char>(fIn)), istreambuf_iterator<char>());
        fIn.close();
        std::ofstream fOut(argv[3], std::ios::binary);
        if (!fOut.is_open())
        {
            cout << "Can not open file" << argv[3] << endl;
            return 0;
        }
        for (int i = 0; i < inp.size() / 12;i++) {
            char z = f_decode(inp.substr(i*12,12));
            fOut << z;
        }
        fOut.close();
        cout << "Decompressed" << endl;
        cout << Timer<double>::elapsed_milliseconds() << " milliseconds" << endl;
        return 0;
    }
    cout << "Wrong command";
    return 0;
}
