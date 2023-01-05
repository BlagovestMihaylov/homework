//
// Created by blago on 5.1.2023 г..
//

#ifndef HOMEWORK_NUMBERSREADER_H
#define HOMEWORK_NUMBERSREADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

class NumbersReader {
public:
    void ReadNumbers();

    std::vector<std::string> SplitInput() const;

    std::string getInput() const;

    void setInput(const std::string &input);

private:
    std::string input;

    static void SplitBraces(std::vector<std::string> &input);
};


#endif //HOMEWORK_NUMBERSREADER_H
