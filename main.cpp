#include <iostream>
#include "mparser.h"


int main() {
    std::string input;
    std::cin >> input;
    mparser a(input);
    std::cout << a.calculate() << '\n';
    return 0;
}
