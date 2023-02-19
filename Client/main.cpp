#include <thread>
#include "SharedBuffer.h"
#include "tcpClient.h"
#include "handlingFunc.h"

#define PORT 1234
static const std::string IP_ADDRESS = "127.0.0.1";


int main() {
    SharedBuffer buffer;
    TcpClient client(PORT, IP_ADDRESS);
    std::thread t1(thread1, std::ref(buffer));
    std::thread t2(thread2, std::ref(buffer), std::ref(client));

    client.start();
    t1.join();
    t2.join();
    return 0;
}