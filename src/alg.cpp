// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string postfix;
    std::string number;

    for (size_t i = 0; i < inf.size(); ++i) {
        char ch = inf[i];
        if (isdigit(ch)) {
            number += ch;
        } else {
            if (!number.empty()) {
                postfix += number + " ";
                number.clear();
            }

            if (ch == '(') {
                stack.push(ch);
            } else if (ch == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    postfix += std::string(1, stack.pop()) + " ";
                }
                stack.pop();
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    char top = stack.peek();
                    bool shouldPop = false;
                    if (ch == '+' || ch == '-') {
                        shouldPop = true;
                    } else if (top == '*' || top == '/') {
                        shouldPop = true;
                    }
                    if (!shouldPop) break;
                    postfix += std::string(1, stack.pop()) + " ";
                }
                stack.push(ch);
            }
        }
    }

    if (!number.empty()) {
        postfix += number + " ";
    }

    while (!stack.isEmpty()) {
        postfix += std::string(1, stack.pop()) + " ";
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::string token;

    for (size_t i = 0; i < post.size(); ++i) {
        char ch = post[i];
        if (isdigit(ch)) {
            token.clear();
            while (i < post.size() && isdigit(post[i])) {
                token += post[i++];
            }
            if (!token.empty()) {
                stack.push(std::stoi(token));
            }
            i--;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (stack.isEmpty()) throw "Not enough operands!";
            int b = stack.pop();
            if (stack.isEmpty()) throw "Not enough operands!";
            int a = stack.pop();

            switch (ch) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }

    if (stack.isEmpty()) throw "No result!";
    return stack.pop();
}
