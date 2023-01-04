//
// Created by blago on 5.1.2023 г..
//

#ifndef HOMEWORK_SEPARATOR_H
#define HOMEWORK_SEPARATOR_H


#include <stack>
#include <string>
#include <vector>

class Separator {
public:
    std::vector<std::string> symbols;
    std::vector<std::string> numbers;
    std::stack<std::string> input_as_stack;

    void Separate(const std::vector<std::string> &input);
};

#endif //HOMEWORK_SEPARATOR_H
