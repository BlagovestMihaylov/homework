//
// Created by blago on 5.1.2023 г..
//

#include <iostream>
#include "Separator.h"

void Separator::Separate(const std::vector<std::string> &input) {
    symbols.clear();
    numbers.clear();
    input_as_rpn = std::stack<std::string>();
    std::stack<std::string> operator_stack;

    for (const std::string &word : input) {
        if (word == "+" || word == "-" || word == "*" || word == "/" || word == "%" || word == "sqrt") {
            // Pop all operators with higher or equal precedence from the operator stack.
            while (!operator_stack.empty() &&
                   HasHigherOrEqualPrecedence(operator_stack.top(), word)) {
                input_as_rpn.push(operator_stack.top());
                operator_stack.pop();
            }
            // Push the current operator onto the operator stack.
            symbols.push_back(word);
            operator_stack.push(word);
        } else if (word == "(") {
            symbols.push_back(word);
            operator_stack.push(word);
        } else if (word == ")") {
            symbols.push_back(word);
            // Pop all operators until we reach the matching opening parenthesis.
            while (!operator_stack.empty() && operator_stack.top() != "(") {
                input_as_rpn.push(operator_stack.top());
                operator_stack.pop();
            }

            // Pop the opening parenthesis.
            if (!operator_stack.empty()) {
                operator_stack.pop();
            }
        } else {
            // This is a number, so push it directly onto the result stack.
            input_as_rpn.push(word);
            numbers.push_back(word);
        }
    }

    // Pop all remaining operators from the stack.
    while (!operator_stack.empty()) {
        input_as_rpn.push(operator_stack.top());
        operator_stack.pop();
    }

//    auto s = input_as_rpn;
//    std::cout<<input_as_rpn.size()<<" size \n\n";
//    while(!s.empty()){
//        std::cout<<s.top()<<" \n\n";
//        s.pop();
//    }
}

bool Separator::HasHigherOrEqualPrecedence(const std::string &op1, const std::string &op2) {
    int precedence1 = GetOperatorPrecedence(op1);
    int precedence2 = GetOperatorPrecedence(op2);
    return precedence1 >= precedence2;
}

int Separator::GetOperatorPrecedence(const std::string &op) {
    if (op == "sqrt") {
        return 3;
    } else if (op == "*" || op == "/" || op == "%") {
        return 2;
    } else if (op == "+" || op == "-") {
        return 1;
    } else {
        return -1;
    }
}

const std::vector<std::string> &Separator::GetSymbols() const {
    return symbols;
}

const std::vector<std::string> &Separator::GetNumbers() const {
    return numbers;
}

const std::stack<std::string> &Separator::GetInputAsRpn() const {
    return input_as_rpn;
}






