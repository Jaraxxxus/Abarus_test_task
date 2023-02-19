//
// Created by jaraxxxus on 19.02.23.
//

#ifndef SERVER_TCPSERVER_H
#define SERVER_TCPSERVER_H


#include <netinet/in.h>
#include <string>

class TcpServer {
public:

    explicit TcpServer(int port);
    ~TcpServer();

    void start(void func(const std::string&));

private:
    int sockfd = 0;
    int opt = 1;
    int clientSocket = 0;
    sockaddr_in addr;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    int addrLength = sizeof(addr);

    void createSocket();

    void makeSocketReusable();

    void addrPrepare(int port);

    void acceptConnection();

    void bindSocketToAddr();
};

#endif //SERVER_TCPSERVER_H
