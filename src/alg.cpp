// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    std::string postfix;
    TStack<char, 100> stack;
    std::map<char, int> priority = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (c == ' ') continue;
        if (isdigit(c)) {
            while (i < inf.size() && isdigit(inf[i])) {
                postfix += inf[i++];
            }
            postfix += ' ';
            i--;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
                postfix += ' ';
            }
            stack.pop();
        } else {
            while (!stack.isEmpty() && stack.peek() != '(' &&
                priority[stack.peek()] >= priority[c]) {
                postfix += stack.pop();
                postfix += ' ';
            }
            stack.push(c);
        }
    }
    while (!stack.isEmpty()) {
        postfix += stack.pop();
        postfix += ' ';
    }
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
    return postfix;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::string numStr;
    for (char c : post) {
        if (c == ' ') {
            if (!numStr.empty()) {
                stack.push(std::stoi(numStr));
                numStr.clear();
            }
            continue;
        }
        if (isdigit(c)) {
            numStr += c;
        } else {
            if (!numStr.empty()) {
                stack.push(std::stoi(numStr));
                numStr.clear();
            }
            int right = stack.pop();
            int left = stack.pop();
            switch (c) {
                case '+': stack.push(left + right); break;
                case '-': stack.push(left - right); break;
                case '*': stack.push(left * right); break;
                case '/': stack.push(left / right); break;
            }
        }
    }
    return stack.pop();
}
