#include <cmath>
#include <stack>
#include <string>
#include "../include/Calculator.hpp"



double Calculator::_execute(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}


std::string Calculator::_get_number_from_str(std::string seq, int& i) {
    std::string res = "";
    for (; i < seq.length(); i++) {
        if (std::isdigit(seq[i])) {
            res += seq[i];
        }
        else {
            i--;
            break;
        }
    }
    return res;
}


std::string Calculator::_convert_to_postfix_notation(const std::string seq) {
    std::string res = "";
    std::stack<char> st;
    for (int i = 0; i < seq.size(); i++) {
        char symbol = seq[i];
        if (std::isdigit(symbol)) {
            res += _get_number_from_str(seq, i) + " ";
        }
        else if (symbol == '(') {
            st.push(symbol);
        }
        else if (symbol == ')') {
            while (st.size() > 0 && st.top() != '(') {
                res += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            if (symbol == '-' && (i == 0 || (i > 1 && _operator_priorities.count(seq[i - 1])))) {
                symbol = '~';
            }
            while (st.size() > 0 && _operator_priorities[st.top()] > _operator_priorities[symbol]) {
                res += st.top();
                st.pop();
            }
            st.push(symbol);
        }
    }
    while (st.size()) {
        res += st.top();
        st.pop();
    }
    return res;
}


double Calculator::calc(const std::string expression)
{
    const std::string postfixExpr = _convert_to_postfix_notation(expression);
    std::stack<double> locals;
    int counter = 0;

    for (int i = 0; i < postfixExpr.length(); i++)
    {
        char c = postfixExpr[i];
				
        if (std::isdigit(c))
        {
            std::string number = _get_number_from_str(postfixExpr, i);
            locals.push(std::stod(number));
        }
        else if (_operator_priorities.count(c))
        {
            counter += 1;
            if (c == '~')
            {
                double last;
                if (locals.size() > 0) {
                    last = locals.top();
                    locals.pop();
                }
                else {
                    last = 0;
                }
                locals.push(_execute('-', 0, last));
                continue;
            }

            double first, second;
            if (locals.size() > 0) {
                second = locals.top();
                locals.pop();
                first = locals.top();
                locals.pop();
            }			
            else {
                second = 0;
                first = 0;
            }
            locals.push(_execute(c, first, second));
        }
    }
		
    return locals.top();
}
