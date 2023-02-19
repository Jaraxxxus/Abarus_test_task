//
// Created by jaraxxxus on 19.02.23.
//
#include <iostream>
#include "inputDataHandling.h"

bool isInputDataCorrect(const std::string& str) {
    if (str.length() > 2 and stoi(str) % 32 == 0) {
        return true;
    }
    return false;
}

void processInputData(const std::string& str) {
    if (isInputDataCorrect(str)) {
        std::cout << "Received data: " << str << std::endl;
    } else {
        std::cout << "Error: Invalid data" << std::endl;
    }
}
