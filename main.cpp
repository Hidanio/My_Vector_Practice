#include "My_Vector.h"

#include <iostream>
int main() {

    My_Vector<int> x{};

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);

    auto d = x[0];
    return 0;
}
