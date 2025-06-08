// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int getOpPriority(char oper) {
    switch (oper) {
        case '(': return 0;
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return -1;
    }
}

std::string infx2pstfx(const std::string& inf) {
    std::string output;
    TStack<char, 100> operators;
    
    for (size_t pos = 0; pos < inf.length(); ++pos) {
        char token = inf[pos];
        
        if (std::isdigit(token)) {
            while (pos < inf.length() && std::isdigit(inf[pos])) {
                output += inf[pos++];
            }
            output += ' ';
            --pos;
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.isempty() && operators.get() != '(') {
                output += operators.get();
                output += ' ';
                operators.pop();
            }
            if (!operators.isempty()) {
                operators.pop(); // Удаляем '('
            }
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!operators.isempty() && 
                   getOpPriority(token) <= getOpPriority(operators.get())) {
                output += operators.get();
                output += ' ';
                operators.pop();
            }
            operators.push(token);
        }
    }
    
    while (!operators.isempty()) {
        output += operators.get();
        output += ' ';
        operators.pop();
    }
    
    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
    
    return output;
}

int eval(const std::string& postfix) {
    TStack<int, 100> values;
    
    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        
        if (std::isdigit(ch)) {
            int number = 0;
            while (i < postfix.length() && std::isdigit(postfix[i])) {
                number = number * 10 + (postfix[i++] - '0');
            }
            values.push(number);
            --i;
        } else if (ch == ' ') {
            continue;
        } else {
            int right = values.get();
            values.pop();
            int left = values.get();
            values.pop();
            
            switch (ch) {
                case '+': values.push(left + right); break;
                case '-': values.push(left - right); break;
                case '*': values.push(left * right); break;
                case '/': values.push(left / right); break;
            }
        }
    }
    
    return values.get();
}
