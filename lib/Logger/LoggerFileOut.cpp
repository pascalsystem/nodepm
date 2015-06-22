/* 
 * File:   LoggerFileOut.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 23 maj 2015, 16:56
 */

#include "LoggerFileOut.h"

void PascalSystem::Logger::LoggerFileOut::write(std::string msg, int type) {
    switch (type) {
        case LOG_TYPE_ERR:
            writerErr->put(msg);
            break;
        default:
            writerOut->put(msg);
    }
}