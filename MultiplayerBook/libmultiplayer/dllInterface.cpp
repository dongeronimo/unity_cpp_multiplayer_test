#include "dllinterface.h"
#include <thread>
#include <queue>

int counter = 0;
UDPSocketPtr udpServerSocket = nullptr;
bool receptionIsRunning = false;
std::shared_ptr<std::thread> serverReceptionThread = nullptr;
struct ReceivedData {
    uint64_t timestamp;
    char data[256];
};
std::queue<ReceivedData> incomingDataQueue;
/// <summary>
/// Resets everything. Should be the first dll function called
/// </summary>
/// <returns></returns>
extern "C" __declspec(dllexport) void __stdcall Initialize() {
    counter = 0;
    udpServerSocket = nullptr;
    receptionIsRunning = false;
    serverReceptionThread = nullptr;
    incomingDataQueue = {};
    StringUtils::Log("Hello World","");
    if (!StartWSAIfWindows()) {
        StringUtils::Log("Could not initialize WSA.","");
    }
}
/// <summary>
/// Shuts down server reception thread if running, shuts down WSA if windows.
/// </summary>
/// <returns></returns>
extern "C" __declspec(dllexport) void __stdcall Shutdown() {
    StringUtils::Log("Shutting down", "");
    if (serverReceptionThread != nullptr) {
        receptionIsRunning = false;
        serverReceptionThread->join();
        serverReceptionThread = nullptr;
    }
    udpServerSocket = nullptr;
    ShutdownWSAIfWindows();
    StringUtils::Log("Goodbye.", "");
}

extern "C" __declspec(dllexport) void __stdcall CreateUDPServer(
    const char* ipAddress, //null terminated ip address
    unsigned short port) 
{
    StringUtils::Log("ip: %s, port: %d .", ipAddress, port);
    //buils the address object
    SocketAddressPtr serverAddr = SocketAddressFactory::CreateIPv4FromString(
        BuildAddrString(ipAddress, port));
    //then creates the udp server socket and binds it
    udpServerSocket = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
    udpServerSocket->SetNonBlockingMode(true);  
    if (udpServerSocket->Bind(*serverAddr)) {
        StringUtils::Log("fail to create the socket.", "");
        receptionIsRunning = false;
    }
    else {
        StringUtils::Log("launching server socket thread.", "");
        receptionIsRunning = true;
        serverReceptionThread = std::make_shared<std::thread>([serverAddr]() {
            while (receptionIsRunning) {
                std::array<unsigned char, 256> buffer{};
                SocketAddress incomingAddress;
                //I'm running the socket in non-blocking mode because if don't i can't join the thread
                //when Shutdown() is invoked. In non-blocking mode i'll only do something if there is
                //data
                int bytesReceived = udpServerSocket->ReceiveFrom(buffer.data(), 256, incomingAddress);
                if (bytesReceived > 0) {
                    StringUtils::Log("Arrived %d bytes", bytesReceived);
                    ReceivedData receivedData;
                    receivedData.timestamp = timeSinceEpochMillisec();
                    std::memcpy(receivedData.data, buffer.data(),
                        sizeof(unsigned char) * buffer.size());
                    incomingDataQueue.push(receivedData);
                }
            }
            StringUtils::Log("server socket thread is over.","");
        });////end of reception thread code
    }
}

extern "C" __declspec(dllexport) unsigned int __stdcall GetMessageQueueSize() {
    return incomingDataQueue.size();
}
extern "C" __declspec(dllexport) bool __stdcall GetIncomingMessage(ReceivedData * outData)
{
    if (incomingDataQueue.size() > 0) {
        ReceivedData data = incomingDataQueue.front();
        incomingDataQueue.pop();
        outData->timestamp = data.timestamp;
        std::memcpy(outData->data, data.data, sizeof(char) * 256);
        return true;
    }
    else {
        return false;
    }
}
extern "C" __declspec(dllexport) int __stdcall GetCounter() {
    return counter;
}

extern "C" __declspec(dllexport) void __stdcall Increment() {
    counter++;
}