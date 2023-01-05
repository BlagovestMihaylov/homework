//
// Created by Blagovest Mihaylov on 5.01.23.
//

#include "NumericChecker.h"

#include <regex>

NumericChecker::NumericChecker() {}

NumericChecker::~NumericChecker() {}

bool NumericChecker::IsDecimal(const std::string &number) const {
    std::regex decimal_regex("^[+-]?\\d+$");
    return std::regex_match(number, decimal_regex);
}

bool NumericChecker::IsHexadecimal(const std::string &number) const {
    std::regex hex_regex("^[+-]?(0x)?[0-9a-fA-F]{1,4}$");
    return std::regex_match(number, hex_regex);
}


bool NumericChecker::IsFraction(const std::string &number) const {
    std::regex fraction_regex("^[+-]?\\d+\\.\\d+$");
    return std::regex_match(number, fraction_regex);
}

std::map<std::string, std::string> NumericChecker::GetNumberTypes(
        const std::vector<std::string> &numbers) const {
    std::map<std::string, std::string> number_types;
    for (const std::string &number: numbers) {
        if (IsDecimal(number)) {
            number_types[number] = "decimal";
        } else if (IsHexadecimal(number)) {
            number_types[number] = "hexadecimal";
        } else if (IsFraction(number)) {
            number_types[number] = "fraction";
        }
    }
    return number_types;
}

std::string NumericChecker::DecimalToBinary(const std::string &decimal) {
    std::string result;
    std::string num = decimal;
    while (num != "0") {
        std::string digit = std::to_string(std::stoi(num) % 2);
        result = digit + result;
        num = std::to_string(std::stoi(num) / 2);
    }
    return result.empty() ? "0" : result;
}

std::string NumericChecker::FractionToBinary(const std::string &fraction, int max_digits) {
    std::string binary;
    std::size_t pos = fraction.find('.');
    if (pos != std::string::npos) {
        std::string integer_part = fraction.substr(0, pos);
        std::string fractional_part = fraction.substr(pos + 1);
        binary = DecimalToBinary(integer_part);
        if (!fractional_part.empty()) {
            binary += '.';
            int count = 0;
            while (!fractional_part.empty() && count < max_digits) {
                double frac = std::stod("0." + fractional_part);
                if (frac == 0) {
                    break;
                }
                frac *= 2;
                if (frac >= 1) {
                    binary += '1';
                    frac -= 1;
                } else {
                    binary += '0';
                }
                fractional_part = std::to_string(frac).substr(2);
                count++;
            }
        }
    } else {
        binary = DecimalToBinary(fraction);
    }
    return binary;
}

std::string NumericChecker::HexadecimalToBinary(const std::string &hexadecimal) {
    std::unordered_map<char, std::string> hex_to_bin = {
            {'0', "0000"},
            {'1', "0001"},
            {'2', "0010"},
            {'3', "0011"},
            {'4', "0100"},
            {'5', "0101"},
            {'6', "0110"},
            {'7', "0111"},
            {'8', "1000"},
            {'9', "1001"},
            {'a', "1010"},
            {'b', "1011"},
            {'c', "1100"},
            {'d', "1101"},
            {'e', "1110"},
            {'f', "1111"},
    };
    std::string binary;
    std::size_t pos = (hexadecimal[0] == '0' && hexadecimal[1] == 'x') ? 2 : 0;
    for (; pos < hexadecimal.size(); ++pos) {
        char c = hexadecimal[pos];
        binary += hex_to_bin[std::tolower(c)];
    }
    return binary;
}

std::map<std::string, std::string> NumericChecker::GetBinaryRepresentations(
        const std::map<std::string, std::string> &number_types) {
    std::map<std::string, std::string> binary_representations;
    for (const auto &pair: number_types) {
        const std::string &number = pair.first;
        const std::string &type = pair.second;
        std::string binary;
        if (type == "decimal") {
            binary = DecimalToBinary(number);
        } else if (type == "fraction") {
            binary = FractionToBinary(number, 5);
        } else if (type == "hexadecimal") {
            binary = HexadecimalToBinary(number);
        }
        binary_representations[number] = binary;
    }
    return binary_representations;
}
