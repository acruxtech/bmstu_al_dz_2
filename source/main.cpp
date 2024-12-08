#include <cctype>
#include <cmath>
#include <iostream>
#include "../include/Calculator.hpp"


int main() {
    Calculator calculator = Calculator();
    std::cout << calculator.calc("-2") << std::endl;
    std::cout << calculator.calc("5*(1+2") << std::endl;
    std::cout << calculator.calc("-2*(18/3^2+(21*(1+2)))") << std::endl;
    std::cout << calculator.calc("-2*exp(18/3^2+(21*(1+2)))*sin(3.14/6)") << std::endl;
    return 0;
}
