/* 
 * File:   CommandStdIn.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 20 maj 2015, 23:04
 */

#include "CommandStdIn.h"

std::string PascalSystem::Command::CommandStdIn::getMessage() {
    std::string buf;
    std::cout << "COMMAND WAIT: ";
    std::getline(std::cin, buf);
    return buf;
}

void PascalSystem::Command::CommandStdIn::sendResponse(std::string data) {
    std::cout << "COMMAND RESPONSE: " << data << std::endl;
}