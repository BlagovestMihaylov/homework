//
// Created by blago on 9.1.2023 г..
//

#ifndef HOMEWORK_INTERFACE_H
#define HOMEWORK_INTERFACE_H

#include "../reading/NumbersReader.h"
#include "../separate/Separator.h"
#include "../numerics/NumericChecker.h"
#include "../calculation/BinaryCalculator.h"

class Interface {

public:
    void Run();

private:
    NumbersReader numbersReader;
    NumericChecker numericChecker;
    Separator separator;
    BinaryCalculator calculator;

    std::string command;
    std::string readCommand();

};


#endif //HOMEWORK_INTERFACE_H
