#include <cmath>
#include <map>
#include <string>


class Calculator {
public:
    double calc(const std::string expression);

private:
    std::map<char, int> _operator_priorities {
        {'(', 0},
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'^', 3},
        {'~', 4},               // унарный минус
    };

    double _execute(char op, double a, double b);

    std::string _get_number_from_str(std::string seq, int& i);

    std::string _convert_to_postfix_notation(const std::string seq);
};
