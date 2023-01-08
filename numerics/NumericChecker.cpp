//
// Created by Blagovest Mihaylov on 5.01.23.
//

#include "NumericChecker.h"

#include <regex>
#include <iostream>

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
    std::regex fraction_regex(R"(^[+-]?\d+\.\d+$)");
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
    bool is_negative = false;

    if(decimal == "-0") return "0";

    std::string copy = decimal;

    if (copy[0] == '-') {
        is_negative = true;
        copy = copy.substr(1);
    }


    std::string result;
    while (copy.size() > 0) {
        int remainder = 0;
        std::string new_copy;
        for (const char &c: copy) {
            int digit = c - '0';
            digit += remainder * 10;
            remainder = digit % 2;
            new_copy += (digit / 2) + '0';
        }
        result = static_cast<char>(remainder + '0') + result;

        copy = new_copy;

        copy.erase(0, copy.find_first_not_of('0'));
    }


    if (is_negative) {
        result = "-" + result;
    }

    return result;

}


std::string NumericChecker::FractionToBinary(const std::string &fraction, int max_digits) {

    std::size_t pos = fraction.find('.');

    std::string integer_part = fraction.substr(0, pos);

    std::string binary = DecimalToBinary(integer_part);

    std::string frac_num = "0." + fraction.substr(pos + 1);

    double frac = std::stod(frac_num);

    std::string fract = getFractionPart(frac, max_digits);

    return binary += fract;
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

    if (hexadecimal == "0x0" || hexadecimal == "0") return "0";

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

std::string NumericChecker::BinaryToDecimal(const std::string &binary) {
    std::string result;
    int value = 0;
    int power = 1;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            value += power;
        }
        power *= 2;
    }
    result = std::to_string(value);
    return result;
}

std::string NumericChecker::BinaryToHexadecimal(const std::string &binary) {
    std::string result;
    int value = 0;
    int power = 1;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            value += power;
        }
        power *= 2;
    }
    result = "";
    while (value > 0) {
        int remainder = value % 16;
        if (remainder < 10) {
            result += std::to_string(remainder);
        } else {
            result += static_cast<char>(remainder - 10 + 'A');
        }
        value /= 16;
    }
    std::reverse(result.begin(), result.end());
    return result;
}




std::string NumericChecker::getFractionPart(double num, int precision) {

    std::string frac = ".";
    double fraction_part = modf(num, nullptr);
    while (precision-- > 0) {
        fraction_part *= 2;
        if (fraction_part >= 1) {
            frac += '1';
            fraction_part -= 1;
        } else {
            frac += '0';
        }
    }

    return frac;
}
