#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int getPriority(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
    std::stringstream postfix;
    TStack<char, 100> stack;
    
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        
        if (isspace(c)) continue;
        
        if (isdigit(c)) {
            while (i < inf.size() && isdigit(inf[i])) {
                postfix << inf[i++];
            }
            postfix << ' ';
            i--;
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix << stack.pop() << ' ';
            }
            stack.pop();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && getPriority(stack.top()) >= getPriority(c)) {
                postfix << stack.pop() << ' ';
            }
            stack.push(c);
        }
    }
    
    while (!stack.isEmpty()) {
        postfix << stack.pop() << ' ';
    }
    
    std::string result = postfix.str();
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;
    
    while (iss >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        }
        else {
            int right = stack.pop();
            int left = stack.pop();
            
            switch (token[0]) {
                case '+': stack.push(left + right); break;
                case '-': stack.push(left - right); break;
                case '*': stack.push(left * right); break;
                case '/': stack.push(left / right); break;
            }
        }
    }
    
    return stack.pop();
}
