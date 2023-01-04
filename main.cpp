#include <iostream>
#include "reading/NumbersReader.h"

int main() {
    NumbersReader reader;
    reader.ReadNumbers();

    std::vector<std::string> input = reader.SplitInput();
    std::cout << "Input:";
    for (const std::string& word : input) {
        std::cout << " " << word;
    }
    std::cout << std::endl;

    return 0;
}
