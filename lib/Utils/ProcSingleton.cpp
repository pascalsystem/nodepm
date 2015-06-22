/* 
 * File:   ProcSingleton.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 25 maj 2015, 20:22
 */

#include "ProcSingleton.h"

bool PascalSystem::Utils::ProcSingleton::createPid(int pid, std::string data) {
    fd = open(getPidFilePath().c_str(), O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0666);
    if (fd <= 0) {
        return false;
    }
    int resultLock = flock(fd, LOCK_EX | LOCK_NB);
    if (resultLock != 0) {
        return false;
    }
    
    std::ostringstream ss;
    ss << pid << std::endl;
    ss << data;
    std::string res = ss.str();
    
    write(fd, res.c_str(), res.length());
    return true;
}

void PascalSystem::Utils::ProcSingleton::destroyPid() {
    flock(fd, LOCK_UN);
    close(fd);
}
