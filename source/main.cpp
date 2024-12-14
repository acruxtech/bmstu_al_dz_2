#include <cctype>
#include <cmath>
#include <exception>
#include <iostream>
#include "../include/Calculator.hpp"


int main() {
    const std::string test_cases[]  {
        "-2",
        "5*(1+2",
        "-x*12",
        "-2*(18/3^2+(21*(1+2)))",
        "-2*exp(18/3^2+(21*(1+2)))*sin(3.14/6)",
        "sin(3.14/2)",
        "cos(0)",
        "tg(3.14/4)",
        "ctg(3.14/4)",
        "exp(2)",
        "x/0",
        "tg(3.14/2)",
        "ctg(0)",
        "x^2 + 2*x + 1",
        "sin(x)",
        "cos(x/2)",
        "tg(x/4)",
        "ctg(x/4)",
        "exp(x)",
    };

    Calculator calculator = Calculator();
    for (const std::string& test : test_cases) {
        try {
            std::cout << calculator.calc(test) << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "error while calc \"" << test << "\" because of: " << e.what() << std::endl;
        }
    }
    return 0;
}
