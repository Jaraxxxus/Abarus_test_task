#include "tcpServer.h"
#include "inputDataHandling.h"

#define PORT 1234


int main(int argc, char const *argv[]) {
    TcpServer server(PORT);
    server.start(processInputData);
    return 0;
}