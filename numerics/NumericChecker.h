//
// Created by Blagovest Mihaylov on 5.01.23.
//

#ifndef HOMEWORK_NUMERICCHECKER_H
#define HOMEWORK_NUMERICCHECKER_H


#include <algorithm>
#include <cctype>
#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>

class NumericChecker {
public:
    NumericChecker();

    ~NumericChecker();

    bool IsDecimal(const std::string &number) const;

    bool IsHexadecimal(const std::string &number) const;

    bool IsFraction(const std::string &number) const;

    std::map<std::string, std::string> GetNumberTypes(
            const std::vector<std::string> &numbers) const;

    std::map<std::string, std::string> GetBinaryRepresentations(
            const std::map<std::string, std::string> &number_types);

    std::string DecimalToBinary(const std::string &decimal);

    std::string FractionToBinary(const std::string &fraction, int max_digits);

    std::string HexadecimalToBinary(const std::string &hexadecimal);
private:
};


#endif //HOMEWORK_NUMERICCHECKER_H
