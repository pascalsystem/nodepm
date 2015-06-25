/* 
 * File:   ProcSingleton.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 25 maj 2015, 20:22
 */

#include "ProcSingleton.h"



void PascalSystem::Utils::ProcSingleton::createPid(int pid) {
    fd = getLockDescriptor(true);
    if (fd == -1) {
        throw std::runtime_error("error create process pid file");
    } else if (fd <= 0) {
        throw std::runtime_error("error lock process pid file");
    }
    
    std::string fileData = getPidFileLine(pid);
    write(fd, fileData.c_str(), fileData.length());
}

void PascalSystem::Utils::ProcSingleton::destroyPid() {
    releaseLockDescriptor(fd);
    fd = -1;
}

bool PascalSystem::Utils::ProcSingleton::isActive() {
    int tempFD = getLockDescriptor();
    if (tempFD > 0) {
        releaseLockDescriptor(tempFD);
        return false;
    } else if (tempFD == -1) {
        return false;
    }
    
    return true;
}

void PascalSystem::Utils::ProcSingleton::releaseLockDescriptor(int lockFD) {
    flock(lockFD, LOCK_UN);
    close(lockFD);
}

int PascalSystem::Utils::ProcSingleton::getLockDescriptor(bool create) {
    int lockFD;
    if (create) {
        lockFD = open(getPidFilePath().c_str(), O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0666);
    } else {
        lockFD = open(getPidFilePath().c_str(), O_RDONLY);
    }
    
    if (lockFD <= 0) {
        return -1;
    }
    int resultLock = flock(lockFD, LOCK_EX | LOCK_NB);
    if (resultLock != 0) {
        close(lockFD);
        return -2;
    }
    
    return lockFD;
}

std::string PascalSystem::Utils::ProcSingleton::getPidFileLine(int pid) {
    std::ostringstream ss;
    ss << pid << std::endl;
    return ss.str();
}