//
// Created by jaraxxxus on 19.02.23.
//

#ifndef CLIENT_TCPCLIENT_H
#define CLIENT_TCPCLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <queue>
#include <mutex>
#include <atomic>

class TcpClient {
public:
    explicit TcpClient(int portNum, std::string ip);

    void addMessage(int message);

    void start();

    ~TcpClient();

private:
    int sockfd;
    sockaddr_in serv_addr;
    std::queue<int> queue;
    std::mutex mutex;
    int portNum;
    std::string ip;
    std::atomic_int size = 0;

    void connectToServer();

    void prepareSocket();

    void sendMessage(const std::string &message) const;

    void createSocket();
};


#endif //CLIENT_TCPCLIENT_H
