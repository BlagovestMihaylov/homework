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

    if (decimal == "-0") return "0";

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
    std::string decimal = "0";
    std::vector<std::string> powers;
    int length = binary.length();

    for (int i = length - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            powers.push_back(powerOfTwo(length - 1 - i));
        } else powers.push_back("0");
    }

    for (int i = 0; i < powers.size(); ++i) {
        if (powers[i] != "0") { decimal = addNumbers(decimal, powers[i]); }
    }

    return decimal;
}

std::string NumericChecker::powerOfTwo(int power) {
    std::string result = "1";
    for (int i = 0; i < power; ++i) {
        int carry = 0;
        for (int j = result.length() - 1; j >= 0; --j) {
            int digit = (result[j] - '0') * 2 + carry;
            if (digit > 9) {
                carry = 1;
                digit -= 10;
            } else {
                carry = 0;
            }
            result[j] = '0' + digit;
        }
        if (carry == 1) {
            result = '1' + result;
        }
    }
    return result;
}

std::string NumericChecker::addNumbers(const std::string a, const std::string b) {
    std::string result;
    int carry = 0;
    int lengthA = a.length();
    int lengthB = b.length();
    int maxLength = std::max(lengthA, lengthB);

    for (int i = 0; i < maxLength; ++i) {
        int digitA = i < lengthA ? a[lengthA - 1 - i] - '0' : 0;
        int digitB = i < lengthB ? b[lengthB - 1 - i] - '0' : 0;
        int sum = digitA + digitB + carry;
        if (sum > 9) {
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }
        result = char('0' + sum) + result;
    }

    if (carry == 1) {
        result = '1' + result;
    }

    return result;
}

std::string NumericChecker::BinaryToHexadecimal(const std::string &binary) {
    std::string result;
    int length = binary.length();

    std::unordered_map<std::string, std::string> binaryHexMap = {
            {"0000", "0"},
            {"0001", "1"},
            {"0010", "2"},
            {"0011", "3"},
            {"0100", "4"},
            {"0101", "5"},
            {"0110", "6"},
            {"0111", "7"},
            {"1000", "8"},
            {"1001", "9"},
            {"1010", "A"},
            {"1011", "B"},
            {"1100", "C"},
            {"1101", "D"},
            {"1110", "E"},
            {"1111", "F"}
    };

    if(length == 4){
        return binaryHexMap.at(binary);
    }

    length--;
    std::vector<std::string> binaries;
    while (length >= 3) {
        std::string hexa;
        hexa.push_back(binary[length - 3]);
        hexa.push_back(binary[length - 2]);
        hexa.push_back(binary[length - 1]);
        hexa.push_back(binary[length]);
        binaries.push_back(hexa);

        if (length < 4) break;

        length -= 4;
    }
    std::string hexa = "";

    for (int i = 0; i <= length; ++i) {
        hexa += binary[i];
    }


    if (hexa.size() > 0) {
        while (hexa.size() != 4) {
            hexa = "0" + hexa;
        }
        binaries.push_back(hexa);
    }

    for (std::string s: binaries) {
        result += binaryHexMap.at(s);
    }

    reverse(result.begin(), result.end());

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

std::vector<std::string> NumericChecker::swapToBinary(std::vector<std::string> splittedInput,
                                                      std::map<std::string, std::string> binaryRepresentation) {
    std::vector<std::string> asBinary;

    for (auto s: splittedInput) {

        if (binaryRepresentation.contains(s))
            asBinary.push_back(binaryRepresentation.at(s));
        else
            asBinary.push_back(s);
    }

    return asBinary;

}
