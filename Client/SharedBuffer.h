//
// Created by jaraxxxus on 19.02.23.
//

#ifndef CLIENT_SHAREDBUFFER_H
#define CLIENT_SHAREDBUFFER_H

#include <mutex>
#include <condition_variable>

class SharedBuffer {
public:
    SharedBuffer() : data(), length(0){}

    void set(std::string& str);

    std::string get();

    ~SharedBuffer() = default;

private:
    int length;
    std::string data;
    std::mutex mutex;
    std::condition_variable cv;
};


#endif //CLIENT_SHAREDBUFFER_H
