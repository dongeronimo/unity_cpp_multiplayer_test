#include <fmt/core.h>
#include <dllinterface.h>
#include "SerializationCommon.h"
#include <thread>
#include <iostream>

bool incomingDataThreadIsRunning = false;
UDPSocketPtr udpServerSocket = nullptr;
std::thread* incomingDataListener = nullptr;

int main(int argc, char** argv)
{
//inicializa WSA se estou no windows
    StartWSAIfWindows();
//Cria o socket do server e põe em loop em um thread proprio
    SocketAddressPtr serverAddr = SocketAddressFactory::CreateIPv4FromString(
        BuildAddrString(serverAddress, serverPort));
    udpServerSocket = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
    udpServerSocket->SetNonBlockingMode(true);
    if (udpServerSocket->Bind(*serverAddr)) { //não conseguiu dar bind
        fmt::println("Fail to bind @{}:{}", serverAddress, serverPort);
        return 1;
    }
    incomingDataThreadIsRunning = true;
    incomingDataListener = new std::thread([] {
        while (incomingDataThreadIsRunning) {
            std::array<unsigned char, 256> buffer{};
            SocketAddress incomingAddress;
            //I'm running the socket in non-blocking mode because if don't i can't join the thread
            //when Shutdown() is invoked. In non-blocking mode i'll only do something if there is
            //data
            int bytesReceived = udpServerSocket->ReceiveFrom(buffer.data(), 256, incomingAddress);
            if (bytesReceived > 0) {
                StringUtils::Log("Arrived %d bytes", bytesReceived);
            }
        }
    });
//Espera o comando de quit
    std::string command = "";
    while (command != "quit") {
        std::cout << "server> ";
        std::cin >> command;
        if (command == "quit") {
            continue;
        }
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }
//Cleanup
    incomingDataThreadIsRunning = false;
    incomingDataListener->join();
    delete incomingDataListener;
    ShutdownWSAIfWindows();
    return 0;
}