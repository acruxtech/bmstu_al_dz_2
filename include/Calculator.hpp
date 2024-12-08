#include <cmath>
#include <map>
#include <string>


class Calculator {
public:
    double calc(const std::string& expression);

private:
    std::map<std::string, std::string> aliases = {
        {"sin", "s"},
        {"cos", "c"},
        {"tag", "t"},
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
            case '/': return a / b;
            case '~': return -a;
            case '^': return pow(a, b);
            case 's': return sin(a);
            case 'c': return cos(a);
            case 't': return tan(a);
            case 'g': return 1 / tan(a);
            case 'e': return exp(a);
            default: return 0;
        }
    }

    std::string _get_number_from_str(const std::string& seq, int& i);

    std::string _replace_with_aliases(const std::string& seq);

    std::string _convert_to_postfix_notation(const std::string& source_seq);
};
