//
// Created by blago on 5.1.2023 г..
//

#ifndef HOMEWORK_TESTS_H
#define HOMEWORK_TESTS_H

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <iostream>
#include <string>

#include "doctest.h"

#include <vector>
#include "../reading/NumbersReader.h"
#include "../separate/Separator.h"
#include "../numerics/NumericChecker.h"

class Tests {
public:
    static void init() {
        doctest::Context().run();
    }

};


TEST_CASE("NumbersReader Test") {
    NumbersReader reader;
    reader.setInput("1 + 2 - 3 * 4 / 5 % 6 sqrt(7)* 8"); //thats a bug - spliting ( and ) with extraspace
    std::vector<std::string> input = reader.SplitInput();
    CHECK(input ==
          std::vector<std::string>{"1", "+", "2", "-", "3", "*", "4", "/", "5", "%", "6", "sqrt", "(", "7", ")", "*",
                                   "8"});
}

TEST_CASE("Separator Test") {
    Separator separator;
    separator.Separate(std::vector<std::string>{"1", "+", "2"});
    CHECK(separator.GetSymbols() == std::vector<std::string>{"+"});
    CHECK(separator.GetNumbers() == std::vector<std::string>{"1", "2"});
    std::stack<std::string> expected_input_as_stack;
    expected_input_as_stack.push("1");
    expected_input_as_stack.push("+");
    expected_input_as_stack.push("2");
    CHECK(separator.GetInputAsStack() == expected_input_as_stack);
}

TEST_CASE("NumericChecker Test") {
    NumericChecker checker;

    CHECK(checker.IsDecimal("123") == true);
    CHECK(checker.IsDecimal("123.45") == false);
    CHECK(checker.IsDecimal("-123") == true);
    CHECK(checker.IsDecimal("+123") == true);
    CHECK(checker.IsDecimal("0x123") == false);

    CHECK(checker.IsHexadecimal("0x123") == true);
    CHECK(checker.IsHexadecimal("0x123.45") == false);
    CHECK(checker.IsHexadecimal("-0x123") == true);
    CHECK(checker.IsHexadecimal("+0x123") == true);
    CHECK(checker.IsHexadecimal("123") == true);
    CHECK(checker.IsHexadecimal("fff") == true);
    CHECK(checker.IsHexadecimal("aa") == true);
    CHECK(checker.IsHexadecimal("0xfff") == true);
    CHECK(checker.IsHexadecimal("0xaa") == true);
    CHECK(checker.IsHexadecimal("0x") == false);
    CHECK(checker.IsHexadecimal("0x123456") == false);
    CHECK(checker.IsHexadecimal("0x123.45") == false);
    CHECK(checker.IsHexadecimal("0x123g") == false);


    CHECK(checker.IsFraction("123.456") == true);
    CHECK(checker.IsFraction("123.456.78") == false);
    CHECK(checker.IsFraction("-123.456") == true);
    CHECK(checker.IsFraction("+123.456") == true);
    CHECK(checker.IsFraction("123.0x456") == false);
    CHECK(checker.IsFraction("123/456") == false);
}

TEST_CASE("NumericChecker Number Types Test") {
    NumericChecker checker;
    std::vector<std::string> numbers = {
            "123", "123.45", "fff", "aa", "0xfff", "0xaa",
    };
    std::map<std::string, std::string> expected_number_types = {
            {"123",    "decimal"},
            {"123.45", "fraction"},
            {"fff",    "hexadecimal"},
            {"aa",     "hexadecimal"},
            {"0xfff",  "hexadecimal"},
            {"0xaa",   "hexadecimal"},
    };
    CHECK(checker.GetNumberTypes(numbers) == expected_number_types);
}

TEST_CASE("NumericChecker types to binary Test") {
    NumericChecker checker;
    std::map<std::string, std::string> number_types = {
            {"123.45", "fraction"},
            {"fff",    "hexadecimal"},
            {"aa",     "hexadecimal"},
            {"0xfff",  "hexadecimal"},
            {"0xaa",   "hexadecimal"},
    };
    std::map<std::string, std::string> expected_binary_representations = {
            {"123",    "1111011"},
            {"123.45", "1111011.01110"},
            {"fff",    "111111111111"},
            {"aa",     "10101010"},
            {"0xfff",  "111111111111"},
            {"0xaa",   "10101010"},
    };
    std::map<std::string, std::string> result = checker.GetBinaryRepresentations(number_types);

    for (const auto &pair: result) {
        const std::string &number = pair.first;
        const std::string &binary = pair.second;
        const std::string &toCheck = expected_binary_representations.at(number);

        CHECK(binary == toCheck);
    }
}

TEST_CASE("NumericChecker::DecimalToBinary Test") {
    NumericChecker checker;
    CHECK(checker.DecimalToBinary("123") == "1111011");
    CHECK(checker.DecimalToBinary("456") == "111001000");
    CHECK(checker.DecimalToBinary("-789") == "-1100010101");
    CHECK(checker.DecimalToBinary("0") == "0");
    CHECK(checker.DecimalToBinary("-0") == "0");
    CHECK(checker.DecimalToBinary("9223372036854775807") == "111111111111111111111111111111111111111111111111111111111111111");
    CHECK(checker.DecimalToBinary("-9223372036854775807") == "-111111111111111111111111111111111111111111111111111111111111111");
    CHECK(checker.DecimalToBinary("0") == "0");
    CHECK(checker.DecimalToBinary("1") == "1");
    CHECK(checker.DecimalToBinary("10") == "1010");
    CHECK(checker.DecimalToBinary("11") == "1011");
    CHECK(checker.DecimalToBinary("100") == "1100100");
    CHECK(checker.DecimalToBinary("1000") == "1111101000");
    CHECK(checker.DecimalToBinary("-1") == "-1");
    CHECK(checker.DecimalToBinary("-10") == "-1010");
    CHECK(checker.DecimalToBinary("-11") == "-1011");
    CHECK(checker.DecimalToBinary("-100") == "-1100100");
    CHECK(checker.DecimalToBinary("-1000") == "-1111101000");
}

TEST_CASE("NumericChecker hexadecimal to binary Test") {
    NumericChecker checker;
    std::vector<std::pair<std::string, std::string>> test_cases = {
            {"0xfff", "111111111111"},
            {"0xaa", "10101010"},
            {"0x0", "0"},
            {"fff", "111111111111"},
            {"aa", "10101010"},
            {"f", "1111"},
            {"a", "1010"},
            {"0", "0"},
    };
    for (const auto &[hexadecimal, expected_binary] : test_cases) {
        std::string binary = checker.HexadecimalToBinary(hexadecimal);
        CHECK(binary == expected_binary);
    }
}

TEST_CASE("NumericChecker Fraction to binary Test") {
    NumericChecker checker;
    CHECK(checker.FractionToBinary("4.47", 3) == "100.011");
    CHECK(checker.FractionToBinary("123.456", 2) == "1111011.01");
    CHECK(checker.FractionToBinary("123.4567", 2) == "1111011.01");
    CHECK(checker.FractionToBinary("0.47", 3) == "0.011");
    CHECK(checker.FractionToBinary("0.456", 2) == "0.01");
    CHECK(checker.FractionToBinary("0.4567", 2) == "0.01");
    CHECK(checker.FractionToBinary("12.3", 3) == "1100.010");
    CHECK(checker.FractionToBinary("1.23", 3) == "1.001");
    CHECK(checker.FractionToBinary("1.234", 3) == "1.001");
}

#endif //HOMEWORK_TESTS_H
