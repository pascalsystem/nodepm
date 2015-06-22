/* 
 * File:   SocketServerAbstract.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 19 maj 2015, 18:18
 */

#include "SocketServerAbstract.h"

void PascalSystem::Socket::SocketServerAbstract::prepareSocket() {
    if (listen(sock, maxQueuedClients) != 0) {
        closeSocket();
        throw std::runtime_error("PascalSystem Server can`t listen socket");
    }
    
    if (!nonIgnoreSinglalPipe) {
        signal(SIGPIPE, SIG_IGN);
    }
    
    if (nonBlock) {
        const int flag = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, flag | O_NONBLOCK);
    }
}

void PascalSystem::Socket::SocketServerAbstract::listenSocket() {
    socketServerBag->socketServer = sock;
    while (running) {
        int clnSock = getAcceptedSocket();
        if (clnSock == -1) {
            usleep(10000);
        } else {
            if (!acceptedSocketHandler(clnSock, socketServerBag)) {
                close(clnSock);
            }
        }
    }
    socketServerBag->socketServer = -1;
    
    closeSocket();
}

void PascalSystem::Socket::SocketServerAbstract::closeSocket() {
    if (sock > 0) {
        close(sock);
        sock = -1;
    }
}

int PascalSystem::Socket::SocketServerAbstract::getAcceptedSocket() {
    struct sockaddr_in cli_addr;
    socklen_t sin_len = sizeof(cli_addr);
    int newSock = accept(sock, (sockaddr*)&cli_addr, &sin_len);
    return (newSock) ? newSock : -1;
}
