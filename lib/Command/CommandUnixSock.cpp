/* 
 * File:   CommandUnixSock.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 25 maj 2015, 18:49
 */

#include "CommandUnixSock.h"

PascalSystem::Command::CommandUnixSock* ___instancePascalSystemCommandUnixSocket = NULL;

std::string PascalSystem::Command::CommandUnixSock::sendMessageToServer(std::string unixPath, std::string cmd) {
    sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, unixPath.c_str());
    socklen_t addLen = sizeof(address);
    
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        std::runtime_error("PascalSystem NodePM can`t create AF_UNIX socket client");
    }
    if (connect(sock, (sockaddr*)&address, addLen) != 0) {
        std::runtime_error("PascalSystem NodePM can`t connect with parent AF_UNIX socket");
    }
    
    if (write(sock, cmd.c_str(), cmd.length()) < cmd.length()) {
        std::runtime_error("PascalSystem NodePM can`t write all command to parent AF_UNIX socket");
    }
    char buf[512];
    int readBytes = read(sock, &buf, 512);
    std::string res = "";
    res.append(buf);
    res = res.substr(0, readBytes);
    close(sock);

    return res;
}

void PascalSystem::Command::CommandUnixSock::reqisterInstance(std::string unixPath) {
    if (___instancePascalSystemCommandUnixSocket == NULL) {
        ___instancePascalSystemCommandUnixSocket = new CommandUnixSock(unixPath);
    } else {
        throw std::runtime_error("PascalSystem command AF_UNIX socket is registered before");
    }
}

PascalSystem::Command::CommandUnixSock* PascalSystem::Command::CommandUnixSock::getInstance() {
    if (___instancePascalSystemCommandUnixSocket == NULL) {
        throw std::runtime_error("PascalSystem command AF_UNIX socket not found registered instance");
    }
    return ___instancePascalSystemCommandUnixSocket;
}

bool PascalSystem::Command::CommandUnixSock::handleSocketData(int sock, PascalSystem::Socket::SocketServerBag* data) {
    char buf[512];
    int readBytes = read(sock, &buf, 512);
    if (readBytes <= 0) {
        close(sock);
        return true;
    }
    std::string cmd = "";
    cmd.append(buf);
    cmd = cmd.substr(0, readBytes);
    std::string res;
    try {
        CommandUnixSock::getInstance();
        res = CommandUnixSock::getInstance()->executeCommand(cmd);
    } catch (std::runtime_error &ex) {
        res = "Error command [runtime_error]: ";
        res.append(ex.what());
    } catch (std::exception &ex) {
        res = "Error command [exception]: ";
        res.append(ex.what());
    }
    if (write(sock, res.c_str(), res.length()) < res.length()) {
        close(sock);
        return true;
    }
    
    close(sock);
    return true;
}

void PascalSystem::Command::CommandUnixSock::run() {
    srv->init();
    srv->run();
}

void PascalSystem::Command::CommandUnixSock::initServerMode(std::string unixPath) {
    srv = new PascalSystem::Socket::SocketServerUnix(unixPath);
    srv->setNonBlock(false);
    srv->setMaxQueuedClients(1);
    srv->setAcceptedSocketHandler(handleSocketData);
}
