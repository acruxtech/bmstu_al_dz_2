#include <cmath>
#include <stack>
#include <stdexcept>
#include <string>
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
            throw std::invalid_argument("unknown symbol in expression");
        }
    }
    while (st.size()) {
        res += st.top();
        res += ' ';
        st.pop();
    }
    return res;
}


double Calculator::calc(const std::string& expression)
{
    const std::string postfix_expr = _convert_to_postfix_notation(expression);
    std::stack<double> locals;
    for (int i = 0; i < postfix_expr.length(); i++)
    {
        char c = postfix_expr[i];
				
        if (std::isdigit(c))
        {
            std::string number = _get_number_from_str(postfix_expr, i);
            locals.push(std::stod(number));
        }
        else if (_operator_priorities.count(c))
        {
            double last = locals.top();
            locals.pop();
            if (c == '~')
            {
                locals.push(_execute('-', 0, last));
                // std::cout << last << " - -> " << _execute('-', 0, last) << std::endl;
                continue;
            }
            if (c == 's' or c == 'c' or c == 't' or c == 'g' or c == 'e') {
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
