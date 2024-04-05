#pragma once
#include "RoboCatPCH.h"
#include <chrono>
#include <cstdint>
inline bool StartWSAIfWindows() {
#ifdef WIN32
    ///Windows demands that I initialize WSA before using sockets
    WSADATA wsaData;
    WORD wVersionRequested;
    wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err) {
        return false;
    }
    else {
        return true;
    }
#else
    ///In linux I dont have to initialize anything
    return true;
#endif
}

inline void ShutdownWSAIfWindows() {
#ifdef WIN32
    WSACleanup();
#endif
}

inline std::string BuildAddrString(const std::string& ip,
    unsigned short port) {
    std::stringstream ss;
    ss << ip << ":" << port;
    return ss.str();
}

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}