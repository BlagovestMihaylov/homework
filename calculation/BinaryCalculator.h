//
// Created by blago on 8.1.2023 г..
//

#ifndef HOMEWORK_BINARYCALCULATOR_H
#define HOMEWORK_BINARYCALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>


class BinaryCalculator {
public:
    std::string Add(const std::string& a, const std::string& b);

    std::string Multiply(const std::string &a, const std::string &b);

    std::string Subtract(const std::string &a, const std::string &b);

    std::string Divide(const std::string &a, const std::string &b);

    bool GreaterThanOrEqual(std::string a, std::string b);

//    std::string SquareRoot(const std::string &number);

    std::string DivideByTwo(const std::string &binary);
};


#endif //HOMEWORK_BINARYCALCULATOR_H
