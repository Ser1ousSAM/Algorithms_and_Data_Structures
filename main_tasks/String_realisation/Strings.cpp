#include <iostream>
#include <cstring>
#include "Str.h"

int main()
{
    Str s = "123";

    std::cout << s << ' ' << strlen(s) << std::endl;
    std::cout << s << ' ' << strlen(s) << std::endl;

    {
        Str t = "456";
        t = s;
        std::cout << t << ' ' << strlen(t) << std::endl;
    }
    std::cout << s << ' ' << strlen(s) << std::endl;

    Str t = "456";
    s = s + t;
    std::cout << s << ' ' << strlen(s) << std::endl;

    s += "33";
    std::cout << s << ' ' << strlen(s) << std::endl;
    return 0;
}