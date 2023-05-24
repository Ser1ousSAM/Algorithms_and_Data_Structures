#include <iostream>
#include "Str.h"

int main() {
    Str s;
    s = "bbbby";
    s += " s zyablamy";
    std::cout << s << '\n';

    Str m;
    m = "bbbb";
    std::cout << s.rfind(m, 4);
    return 0;
}