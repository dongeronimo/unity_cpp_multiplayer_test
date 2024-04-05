#include "RoboCatPCH.h"
#include <array>
#include <iostream>
int main() {
    //WSA initialization to be able to use winsocks
#ifdef WIN32
    WSADATA wsaData;
    WORD wVersionRequested;
    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);
#endif
    UDPSocketPtr udpSocket = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
    SocketAddressPtr serverAddr = SocketAddressFactory::CreateIPv4FromString("0.0.0.0:9999");
    udpSocket->Bind(*serverAddr);
    //waits for some data
    std::array<char, 256> buffer{};
    SocketAddress incomingAddress;
    udpSocket->ReceiveFrom(buffer.data(), 256, incomingAddress);
    std::cout << "chegou" << std::endl;
    //after we are done, cleanup WSA
    WSACleanup();
    return 0;
}