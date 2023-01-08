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
    void Separate(const std::vector<std::string> &input);

    const std::vector<std::string> &GetSymbols() const;

    const std::vector<std::string> &GetNumbers() const;

    const std::stack<std::string> &GetInputAsRpn() const;

private:
    std::vector<std::string> symbols;
    std::vector<std::string> numbers;
    std::stack<std::string> input_as_rpn;

    bool HasHigherOrEqualPrecedence(const std::string &op1, const std::string &op2);

    int GetOperatorPrecedence(const std::string &op);
};

#endif //HOMEWORK_SEPARATOR_H
