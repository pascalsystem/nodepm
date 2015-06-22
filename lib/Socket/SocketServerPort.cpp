/* 
 * File:   SocketServerPort.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 19 maj 2015, 19:45
 */

#include "SocketServerPort.h"

void PascalSystem::Socket::SocketServerPort::createSocket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0) {
        throw std::runtime_error("PascalSystem Server can`t open socket");
    }
    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));    
}

void PascalSystem::Socket::SocketServerPort::bindSocket() {
    struct sockaddr_in sockAddress;
    bzero((char*)&sockAddress, sizeof(sockAddress));
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons(port);
    
    if (bind(sock, (struct sockaddr*)&sockAddress, sizeof(sockAddress)) != 0) {
        closeSocket();
        throw std::runtime_error("PascalSystem Server can`t bind socket");
    }
}