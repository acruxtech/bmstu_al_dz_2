#include <cmath>
#include <map>
#include <string>
#include <stdexcept>


class Calculator {
public:
    Calculator(double eps = 1e-6) {
        _eps = eps;
    }
    
    double calc(const std::string& expression);
    
private:
    double _x, _eps;

    std::map<std::string, std::string> aliases = {
        {"sin", "s"},
        {"cos", "c"},
        {"tg", "t"},
        {"ctg", "g"},
        {"exp", "e"}
    };

    std::map<char, int> _operator_priorities {
        {'(', 0},
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'^', 3},
        {'~', 4},               // унарный минус
        {'s', 4},               // sin
        {'c', 4},               // cos
        {'t', 4},               // tan
        {'g', 4},              // ctg
        {'e', 4},              // exp
    };

    double _execute(char op, double a, double b = 0) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) {
                    throw std::invalid_argument("0 is incorrect value for division");
                }
                return a / b;
            case '~': return -a;
            case '^': return pow(a, b);
            case 's': return sin(a);
            case 'c': return cos(a);
            case 't':
                if (std::abs(a - M_PI_2) < _eps) {
                    std::string message = std::to_string(a);
                    message += " is incorrect value for tg";
                    throw std::invalid_argument(message);
                } 
                return tan(a);
            case 'g': 
                if (a == 0) {
                    throw std::invalid_argument("0 is incorrect value for ctg");
                }
                return 1 / tan(a);
            case 'e': return exp(a);
            default: throw std::invalid_argument("unknown operator");
        }
    }

    std::string _get_number_from_str(const std::string& seq, int& i);

    std::string _replace_with_aliases(const std::string& seq);

    std::string _convert_to_postfix_notation(const std::string& source_seq);

    void _check_postfix_notation_validity(const std::string& seq);
};
