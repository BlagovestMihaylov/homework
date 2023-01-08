//
// Created by blago on 9.1.2023 г..
//

#include "Interface.h"

void Interface::Run() {

    std::cout
            << "\n\n\n\n\nWelcome to the amazing (and a little broken) calculator!\nWe have only one command for the ease of use\nP.S. do not go hard on square roots and fractions\n\n\n";

    do {
        readCommand();

        numbersReader.ReadNumbers();

        std::vector<std::string> splittedInput = numbersReader.SplitInput();

        std::map<std::string, std::string> typesByNumbers = numericChecker.GetNumberTypes(splittedInput);

        std::map<std::string, std::string> binaryRepresentation = numericChecker.GetBinaryRepresentations(typesByNumbers);

        std::vector<std::string> splittedInputAsBinary = numericChecker.swapToBinary(splittedInput, binaryRepresentation);

        separator.Separate(splittedInputAsBinary);

        std::stack<std::string> inputAsReversedPolishNotation = separator.GetInputAsRpn();

        std::string resultInBinary = calculator.evaluateRpn(inputAsReversedPolishNotation);

        std::string resultInDecimal = numericChecker.BinaryToDecimal(resultInBinary);

        std::string resultInHexadecimal = numericChecker.BinaryToHexadecimal(resultInBinary);

        std::cout<<numbersReader.getInput()<<" = "<<resultInDecimal<<" (which is "<< resultInBinary<<" in binary and "<<resultInHexadecimal<<" in hexadecimal\n";

    } while (command != "exit" || command != "2");

    std::cout << "\n\nGoodbye, I hope that, I did well\n\n";
}

std::string Interface::readCommand() {
    std::cout << "Type exit to exit or press enter to continue";
    std::getline(std::cin, command);
    return command;
}
