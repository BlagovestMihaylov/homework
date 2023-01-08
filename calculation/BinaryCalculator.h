//
// Created by blago on 8.1.2023 г..
//

#ifndef HOMEWORK_BINARYCALCULATOR_H
#define HOMEWORK_BINARYCALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>
#include <stack>


class BinaryCalculator {
public:
    std::string Add(const std::string& a, const std::string& b);

    std::string Multiply(const std::string &a, const std::string &b);

    std::string Subtract(const std::string &a, const std::string &b);

    std::string Divide(const std::string &a, const std::string &b);

    bool GreaterThanOrEqual(std::string a, std::string b);

//    std::string SquareRoot(const std::string &number);

    std::string DivideByTwo(const std::string &binary);

    std::string calculate(int a, int b, const std::string &operation);

    bool isOperation(const std::string &op);

    std::string calculate(std::string a, std::string, const std::string &operation);


    std::string evaluateRpn(std::stack<std::string> rpn);

    std::vector<std::string> stackToVector(std::stack<std::string> st);
};


#endif //HOMEWORK_BINARYCALCULATOR_H
