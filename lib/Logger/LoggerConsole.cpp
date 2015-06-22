/* 
 * File:   LoggerConsole.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 13 maj 2015, 21:19
 */

#include "LoggerConsole.h"

void PascalSystem::Logger::LoggerConsole::write(std::string msg, int type) {
    switch (type) {
        case LOG_TYPE_ERR:
            std::cerr << msg << std::endl;
            break;
        default:
            std::cout << msg << std::endl;
    }
}