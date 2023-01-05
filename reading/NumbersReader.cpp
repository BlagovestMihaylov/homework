//
// Created by blago on 5.1.2023 г..
//
#include "NumbersReader.h"

void NumbersReader::ReadNumbers() {
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);
}

std::vector<std::string> NumbersReader::SplitInput() const {
    std::istringstream iss(input);
    std::vector<std::string> input;
    for (std::string word; iss >> word;) {
        input.push_back(word);
    }
    SplitBraces(input);
    return input;
}

std::string NumbersReader::getInput() const {
    return input;
}

void NumbersReader::setInput(const std::string &input) {
    this->input = input;
}


void NumbersReader::SplitBraces(std::vector<std::string> &input) {
    std::vector<std::string> result;
    for (const std::string &word: input) {
        std::string w = word;
        std::size_t pos = w.find('(');
        while (pos != std::string::npos) {
            result.push_back(w.substr(0, pos));
            result.emplace_back("(");
            w = w.substr(pos + 1);
            pos = w.find('(');
        }
        pos = w.find(')');
        while (pos != std::string::npos) {
            result.push_back(w.substr(0, pos));
            result.emplace_back(")");
            w = w.substr(pos + 1);
            pos = w.find(')');
        }
        result.push_back(w);
    }
    input = result;
}

