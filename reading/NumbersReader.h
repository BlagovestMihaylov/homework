//
// Created by blago on 5.1.2023 г..
//

#ifndef HOMEWORK_NUMBERSREADER_H
#define HOMEWORK_NUMBERSREADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class NumbersReader {
public:
    void ReadNumbers();
    std::vector<std::string> SplitInput() const;
    std::string str() const;

private:
    std::string str_;
};


#endif //HOMEWORK_NUMBERSREADER_H
