//
// Created by blago on 5.1.2023 г..
//

#include "Separator.h"

void Separator::Separate(const std::vector<std::string> &input) {
    symbols.clear();
    numbers.clear();
    input_as_stack = std::stack<std::string>();
    for (const std::string &word: input) {
        if (word == "+" || word == "-" || word == "*" || word == "/" || word == "%" || word == "sqrt" || word == "(" ||
            word == ")") {
            symbols.push_back(word);
        } else {
            numbers.push_back(word);
        }
        input_as_stack.push(word);
    }
}






