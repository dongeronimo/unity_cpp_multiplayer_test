#include <fmt/core.h>
#include <dllinterface.h>
#include "SerializationCommon.h"
#include <random>
#include <iostream>
#include <curses.h>
#include <thread>
std::string name;
USHORT incomingPort;

UDPSocketPtr inboundSocket = nullptr;
UDPSocketPtr outboundSocket = nullptr;

int main(int argc, char** argv)
{
   
    StartWSAIfWindows();
    std::cout << "Name:";
    std::cin >> name;
    std::cout << "Port:";
    std::string strPort;
    std::cin >> strPort;
    incomingPort = std::stoi(strPort);
    //inicializa WSA se estou no windows
    StartWSAIfWindows();
    //cria o socket de recepção
    SocketAddressPtr inboundSocketAddr = SocketAddressFactory::CreateIPv4FromString(
        BuildAddrString("0.0.0.0", incomingPort));
    inboundSocket = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
    inboundSocket->SetNonBlockingMode(true);
    if (inboundSocket->Bind(*inboundSocketAddr)) {
        fmt::println("Fail to bind @{}:{}", "0.0.0.0", incomingPort);
        return 1;
    }
    //cria o socket de envio
    SocketAddressPtr outboundSocketAddr = SocketAddressFactory::CreateIPv4FromString(
        BuildAddrString("127.0.0.1", serverPort)
    );
    outboundSocket = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
    outboundSocket->SetNonBlockingMode(true);
    std::string fooStr = "foobar!";
    std::array<BYTE, 256> outBuffer = {};
    std::memcpy(outBuffer.data(), fooStr.c_str(), fooStr.size());
    //envia a msg de hello pro server pro server registrar esse host.
    outboundSocket->SendTo(outBuffer.data(), 256, *outboundSocketAddr);
    //main loop
    while (true) {
        std::array<unsigned char, 256> buffer{};
        SocketAddress incomingAddress;
        int bytesReceived = inboundSocket->ReceiveFrom(buffer.data(), 256, incomingAddress);
        if (bytesReceived > 0) {
            fmt::println("Arrived {} bytes", bytesReceived);
        }
    }
    //Cleanup
    inboundSocket = nullptr;
    outboundSocket = nullptr;
    ShutdownWSAIfWindows();
    return 0;
}