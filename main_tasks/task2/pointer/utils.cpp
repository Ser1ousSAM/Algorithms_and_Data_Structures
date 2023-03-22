#include "utils.h"

void utils::Swap(int &a, int &b) {
    int * val1, * val2, temp;
    val1 = &a;
    val2 = &b;
    temp = * val1;
    *val1 = *val2;
    *val2 = temp;
}

void utils::Swap(int *pa, int *pb) {
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}
