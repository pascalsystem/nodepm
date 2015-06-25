/* 
 * File:   SocketServerUnix.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 25 maj 2015, 18:56
 */

#include <sys/stat.h>

#include "SocketServerUnix.h"

void PascalSystem::Socket::SocketServerUnix::createSocket() {
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock <= 0) {
        throw std::runtime_error("PascalSystem Server can`t open AF_UNIX socket");
    }

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));        
}

void PascalSystem::Socket::SocketServerUnix::bindSocket() {
    struct sockaddr_un sockAddress;
    bzero((char*)&sockAddress, sizeof(sockAddress));
    sockAddress.sun_family = AF_UNIX;
    strcpy(sockAddress.sun_path, unixPath.c_str());
    
    unlink(unixPath.c_str());

    int bindResult = bind(sock, (struct sockaddr*)&sockAddress, sizeof(sockAddress));
    if (bindResult != 0) {
        closeSocket();
        std::ostringstream ss;
        ss << "PascalSystem Server can`t bind AF_UNIX socket";
        ss << " [code: " << bindResult << "]";
        throw std::runtime_error(ss.str().c_str());
    }
    
    chmod(unixPath.c_str(), 0777);
}