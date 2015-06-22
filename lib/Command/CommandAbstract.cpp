/* 
 * File:   CommandAbstract.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 20 maj 2015, 23:00
 */

#include "CommandAbstract.h"

void PascalSystem::Command::CommandAbstract::run() {
    std::string req;
    do {
        req = getMessage();
        if (isExitCommand(req)) {
            break;
        }
        
        std::string res = handler(req);
        sendResponse(res);
    } while (true);
}

std::string PascalSystem::Command::CommandAbstract::executeCommand(std::string cmd) {
    return handler(cmd);
}
