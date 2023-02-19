//
// Created by jaraxxxus on 19.02.23.
//

#include "tcpClient.h"

TcpClient::TcpClient(int portNum, std::string ip) {
    this->ip = ip;
    this->portNum = portNum;
    prepareSocket();
}

void TcpClient::addMessage(int message) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(message);
    size = queue.size();
}

void TcpClient::start() {
    connectToServer();
    socklen_t len = sizeof(serv_addr);
    while (true) {
        if (getpeername(sockfd, (sockaddr *) &serv_addr, &len) == -1) {
            close(sockfd);
            prepareSocket();
            connectToServer();
            continue;
        }

        while (size) {
            if (getpeername(sockfd, (sockaddr *) &serv_addr, &len) == -1)
                break;
            std::string message;
            {
                std::lock_guard<std::mutex> lock(mutex);
                message = std::to_string(queue.front());
                queue.pop();
                --size;
            }

            sendMessage(message);
            sleep(1);
        }
    }
}

void TcpClient::connectToServer() {
    if (connect(sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        std::cerr << "Connection failed, errno = " << errno << " - " << std::strerror(errno) << std::endl;
        while (true) {
            if (connect(sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
                sleep(3);
            }
            break;
        }
    }
}

void TcpClient::createSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket, errno = " << errno << " - " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void TcpClient::prepareSocket() {
    createSocket();
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
}

void TcpClient::sendMessage(const std::string &message) const {
    char buffer[1024];
    strcpy(buffer, message.c_str());
    if (write(sockfd, buffer, strlen(buffer)) < 0) {
        std::cerr << "Error writing to socket, errno = " << errno << " - " << std::strerror(errno) << std::endl;
    }
    memset(buffer, 0, 1024);
}

TcpClient::~TcpClient() {
    close(sockfd);
}
