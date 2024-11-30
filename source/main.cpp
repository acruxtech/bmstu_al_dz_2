#include <cctype>
#include <cmath>
#include <map>
#include <stack>
#include <string>
#include <iostream>


std::map<char, int> operator_priorities {
    {'(', 0},
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
    {'~', 4},               // унарный минус
};


double Execute(char op, double first, double second) {
    switch (op) {
        case '+': return first + second;
        case '-': return first - second;
        case '*': return first * second;
        case '/': return first / second;
        case '^': return pow(first, second);
        default: return 0;
    }
}


std::string get_string_number(std::string seq, int& i) {
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


std::string convert_to_postfix_notation(const std::string seq) {
    std::string res = "";
    std::stack<char> st;
    for (int i = 0; i < seq.size(); i++) {
        char symbol = seq[i];
        if (std::isdigit(symbol)) {
            res += get_string_number(seq, i) + " ";
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
            if (symbol == '-' && (i == 0 || (i > 1 && operator_priorities.count(seq[i - 1])))) {
                symbol = '~';
            }
            while (st.size() > 0 && operator_priorities[st.top()] > operator_priorities[symbol]) {
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


double calc(const std::string postfixExpr)
{
    std::stack<double> locals;
    int counter = 0;

    for (int i = 0; i < postfixExpr.length(); i++)
    {
        char c = postfixExpr[i];
				
        if (std::isdigit(c))
        {
            std::string number = get_string_number(postfixExpr, i);
            locals.push(std::stod(number));
        }
        else if (operator_priorities.count(c))
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
                locals.push(Execute('-', 0, last));
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
            locals.push(Execute(c, first, second));
        }
    }
		
    return locals.top();
}


int main() {
    // std::cout << convert_to_postfix_notation("1+2+3*1+12") << std::endl;
    std::cout << convert_to_postfix_notation("5*(1+2)") << std::endl;
    std::cout << calc(convert_to_postfix_notation("(1+2)*5+1")) << std::endl;
    return 0;
}