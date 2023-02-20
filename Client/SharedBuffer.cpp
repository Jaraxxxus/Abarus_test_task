//
// Created by jaraxxxus on 19.02.23.
//

#include "SharedBuffer.h"

void SharedBuffer::set(std::string &str) {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]() { return length == 0; });
    data = str;
    length = data.length();
    cv.notify_one();
}

std::string SharedBuffer::get() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]() { return length != 0; });
    std::string result = std::move(data);
    data = "";
    length = 0;
    return result;
}
