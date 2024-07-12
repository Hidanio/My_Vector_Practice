#include "My_Vector.h"
#include <iostream>
#include <vector>
int main() {

/*
    My_Vector<int> x{};
    My_Vector<int> y{};
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
*/


/*    My_Vector<Printer> p;

    p.push_back(Printer());
    p.pop_back();*/

/*    My_Vector<My_Vector<int>> diffV;

    diffV.push_back(My_Vector<int>());
    diffV.pop_back();*/

    /*
    auto d = x[0];
    x=y;

    x = std::move(y);*/


    std::vector<Printer> stdPrinter;

    for(auto i = 0; i< 50; ++i){
        std::cout << i << "\n";
        stdPrinter.emplace_back();
    }

    return 0;
}
