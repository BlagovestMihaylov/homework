//
// Created by blago on 5.1.2023 г..
//

#ifndef HOMEWORK_TESTS_H
#define HOMEWORK_TESTS_H

#define DOCTEST_CONFIG_IMPLEMENT

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../reading/NumbersReader.h"
#include "../separate/Separator.h"
#include "doctest.h"

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
          std::vector<std::string>{"1", "+", "2", "-", "3", "*", "4", "/", "5", "%", "6", "sqrt", "(", "7", ")","*", "8"});
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


#endif //HOMEWORK_TESTS_H
