#include <cctype>
#include <cmath>
#include <iostream>
#include "../include/Calculator.hpp"


int main() {
    Calculator calculator = Calculator();
    std::cout << calculator.calc("5*(1+2)") << std::endl;
    return 0;
}
