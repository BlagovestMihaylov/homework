//
// Created by blago on 5.1.2023 г..
//
#include "NumbersReader.h"

void NumbersReader::ReadNumbers() {
    std::cout << "Enter a string: ";
    std::getline(std::cin, str_);
}

std::vector<std::string> NumbersReader::SplitInput() const {
    std::istringstream iss(str_);
    std::vector<std::string> input;
    for (std::string word; iss >> word; ) {
        input.push_back(word);
    }
    return input;
}

std::string NumbersReader::str() const {
    return str_;
}

