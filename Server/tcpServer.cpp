//
// Created by jaraxxxus on 19.02.23.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "tcpServer.h"


TcpServer::TcpServer(int port) {
    createSocket();
    makeSocketReusable();
    addrPrepare(port);
    bindSocketToAddr();
}

void TcpServer::start(void (*func)(const std::string&)) {
    if (listen(sockfd, SOMAXCONN) == -1) {
        std::cerr << "cant listen this port, errno = " << errno << " - " << std::strerror(errno);
        exit(EXIT_FAILURE);
    }
    std::cout << "Waiting for incoming connection from client..." << std::endl;
    acceptConnection();

    while (true) {
        char buff[1024] = {0};
        int bytesReceived = recv(clientSocket, buff, 1024, 0);

        if (bytesReceived <= 0) {
            std::cerr << "Connection lost. Waiting for new incoming connection..." << std::endl;
            close(clientSocket);
            acceptConnection();
            continue;
        }
        std::string data(buff, bytesReceived);
        func(data);

        memset(buff, 0, 1024);
    }
}

void TcpServer::createSocket() {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "socket() failed, errno = " << errno << " - " << std::strerror(errno);
        exit(EXIT_FAILURE);
    }
}

void TcpServer::makeSocketReusable() {
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "problems with setsockopt() function, errno = " << errno << " - " << std::strerror(errno);
        exit(EXIT_FAILURE);
    }
}

void TcpServer::acceptConnection() {
    if ((clientSocket = accept(sockfd, (sockaddr *) &client, (socklen_t *) &clientSocket)) < 0)     {
        std::cerr << "problems in accept() func, errno = " << errno << " - " << std::strerror(errno);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to client" << std::endl;
}

void TcpServer::bindSocketToAddr() {
    if (bind(sockfd, (sockaddr *) &addr, sizeof(addr)) < 0) {
        std::cerr << "Unsuccessful bind, errno = " << errno << " - " << std::strerror(errno)<<std::endl;
        exit(EXIT_FAILURE);
    }
}

void TcpServer::addrPrepare(int port) {
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
}

TcpServer::~TcpServer() {
    memset(&addr, 0, addrLength);
    close(sockfd);
    close(clientSocket);
}
