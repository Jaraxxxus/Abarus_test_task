//
// Created by jaraxxxus on 19.02.23.
//
#include <sstream>
#include <thread>
#include <algorithm>
#include "handlingFunc.h"
static const int MAX_LENGTH = 64;

bool isInputStringCorrect(std::string str) {
    if (str.length() > MAX_LENGTH) {
        std::cerr << "Input string is too long." << std::endl;
        return false;
    }
    if (!std::all_of(str.begin(), str.end(), ::isdigit)) {
        std::cerr << "Input string contains non-digit characters." << std::endl;
        return false;
    }
    return true;
}

std::stringstream ChangeEvenToKB(const std::string &str) {
    std::stringstream ss;
    for (char ch: str) {
        if ((ch - '0') % 2 == 0) {
            ss << "KB";
        } else {
            ss << ch;
        }
    }
    return ss;
}

std::string processString(std::string str) {
    std::sort(str.begin(), str.end(), std::greater<>());
    std::stringstream ss = ChangeEvenToKB(str);
    return ss.str();
}

void thread1(SharedBuffer &buffer) {
    //std::cout << "Thread ID " << std::this_thread::get_id() << std::endl;
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (!isInputStringCorrect(input)) {
            std::cout << "Error: Input string is incorrect" << std::endl;
            continue;
        }
        std::string result = processString(input);
        buffer.set(result);
    }
}

int digitOnlySum(const std::string &str) {
    int sum = 0;
    for (auto c: str) {
        if (::isdigit(c)) {
            sum += c - '0';
        }
    }
    return sum;
}

void thread2(SharedBuffer &buffer, TcpClient &client) {
    //std::cout << "Thread ID " << std::this_thread::get_id() << std::endl;
    while (true) {
        std::string input = buffer.get();
        std::cout << "Sorted and modified input: " << input << std::endl;

        int sum = digitOnlySum(input);
        client.addMessage(sum);
    }
}
