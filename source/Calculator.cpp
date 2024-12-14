#include <cmath>
#include <cstddef>
#include <stack>
#include <stdexcept>
#include <string>
#include <iostream>
#include "../include/Calculator.hpp"


std::string Calculator::_get_number_from_str(const std::string& seq, int& i) {
    std::string res = "";
    for (; i < seq.length(); i++) {
        if (std::isdigit(seq[i]) or seq[i] == '.') {
            res += seq[i];
        }
        else {
            i--;
            break;
        }
    }
    return res;
}


std::string Calculator::_replace_with_aliases(const std::string& seq) {
    std::string res = seq;
    for (const auto& alias : aliases) {
        size_t pos = 0;
        while ((pos = res.find(alias.first)) != std::string::npos) {
            res.replace(pos, alias.first.length(), alias.second);
        }
    }
    return res;
}


std::string Calculator::_convert_to_postfix_notation(const std::string& source_seq) {
    std::string res = "";
    std::stack<char> st;

    std::string seq = _replace_with_aliases(source_seq);

    for (int i = 0; i < seq.size(); i++) {
        char symbol = seq[i];
        if (symbol == ' ') continue;
        else if (symbol == 'x') {
            res += "x ";
        }
        else if (std::isdigit(symbol)) {
            res += _get_number_from_str(seq, i) + " ";
        }
        else if (symbol == '(') {
            st.push(symbol);
        }
        else if (symbol == ')') {
            while (st.size() > 0 && st.top() != '(') {
                res += st.top();
                res += ' ';
                st.pop();
            }
            st.pop();
        }
        else if (_operator_priorities.count(symbol)) {
            if (symbol == '-' && (i == 0 || (i > 1 && _operator_priorities.count(seq[i - 1])))) {
                symbol = '~';
            }
            while (st.size() > 0 && _operator_priorities[st.top()] > _operator_priorities[symbol]) {
                res += st.top();
                res += ' ';
                st.pop();
            }
            st.push(symbol);
        }
        else {
            std::string message = "unknown symbol ";
            message += symbol;
            message += " in expression";
            throw std::invalid_argument(message);
        }
    }
    while (st.size()) {
        res += st.top();
        res += ' ';
        st.pop();
    }
    _check_postfix_notation_validity(res);
    return res;
}


void Calculator::_check_postfix_notation_validity(const std::string& seq) {
    if (seq.find_first_of("()") != std::string::npos) {
        throw std::invalid_argument("malformed expression");
    }
    std::stack<double> locals;
    for (int i = 0; i < seq.length(); i++)
    {
        char c = seq[i];
		
        if (c == ' ') continue;
        else if (std::isdigit(c))
        {
            std::string number = _get_number_from_str(seq, i);
            locals.push(std::stod(number));
        }
        else if (c == 'x') {
            locals.push(c);
        }
        else if (_operator_priorities.count(c))
        {
            if (locals.empty()) throw std::invalid_argument("malformed expression");
            double last = locals.top();
            locals.pop();
            if (c == '~' or c == 's' or c == 'c' or c == 't' or c == 'g' or c == 'e') {
                if (last == 'x') {
                    locals.push(last);
                }
                else {
                    locals.push(_execute(c, last));
                }
                continue;
            }

            if (locals.empty()) throw std::invalid_argument("malformed expression");
            double first = locals.top();
            locals.pop();
            if (last == 'x' || first == 'x') {
                locals.push('x');
            }
            else {
                locals.push(_execute(c, first, last));		
            }
        }
        else if (c == '(' or c == ')') {
            throw std::invalid_argument("brackets are placed incorrectly");
        }
    }
	
    if (locals.size() != 1) {
        throw std::invalid_argument("malformed expression");
    }
}



double Calculator::calc(const std::string& expression)
{
    std::string postfix_expr = _convert_to_postfix_notation(expression);

    if (postfix_expr.find("x") != std::string::npos) {
        std::cout << "enter the value of x: ";
        std::cin >> _x;
        size_t pos;
        while ((pos = postfix_expr.find('x')) != std::string::npos) {
            postfix_expr.replace(pos, 1, std::to_string(_x));
        }
    }

    std::stack<double> locals;
    for (int i = 0; i < postfix_expr.length(); i++)
    {
        char c = postfix_expr[i];
		
        if (c == ' ') continue;
        else if (std::isdigit(c))
        {
            std::string number = _get_number_from_str(postfix_expr, i);
            locals.push(std::stod(number));
        }
        else if (_operator_priorities.count(c))
        {
            double last = locals.top();
            locals.pop();
            if (c == '~' or c == 's' or c == 'c' or c == 't' or c == 'g' or c == 'e') {
                locals.push(_execute(c, last));
                // std::cout << last << " " << c << " -> " << _execute(c, last) << std::endl;
                continue;
            }
            double first = locals.top();
            locals.pop();
            locals.push(_execute(c, first, last));		
            // std::cout << first << " " << c << " " << last << " -> " << _execute(c,first, last) << std::endl;
        }
    }
		
    return locals.top();
}
