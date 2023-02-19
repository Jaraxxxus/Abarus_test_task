//
// Created by jaraxxxus on 19.02.23.
//

#ifndef CLIENT_HANDLINGFUNC_H
#define CLIENT_HANDLINGFUNC_H

#include <iostream>
#include "SharedBuffer.h"
#include "tcpClient.h"

bool isInputStringCorrect(std::string str);

std::stringstream ChangeEvenToKB(const std::string &str);

std::string processString(std::string str);

void thread1(SharedBuffer &buffer);

int digitOnlySum(const std::string &str);

void thread2(SharedBuffer &buffer, TcpClient &client);

#endif //CLIENT_HANDLINGFUNC_H
