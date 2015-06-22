/* 
 * File:   LoggerAbstract.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 12 maj 2015, 22:13
 */

#include "LoggerAbstract.h"

void* PascalSystem::Logger::LoggerAbstract::handlerThreadLoggerStruct(void* data) {
    ThreadLoggerStruct* structData = ((ThreadLoggerStruct*)data);
    LoggerAbstract* loggerItem = ((LoggerAbstract*)structData->logger);
    
    loggerItem->writeFromHandler(
            structData->handler,
            structData->type,
            structData->maxBuf
    );
}

std::string PascalSystem::Logger::LoggerAbstract::getLogTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    
    strftime(buf, sizeof(buf), logDateTimeFormat, &tstruct);

    return buf;
}

void PascalSystem::Logger::LoggerAbstract::sendMessage(std::string msg, int type) {
    std::ostringstream ss;
    ss << "[" << getLogTime() << "] [";
    switch (type) {
        case LOG_TYPE_ERR:
            ss << "ERR";
            break;
        case LOG_TYPE_INFO:
            ss << "INFO";
            break;
        default:
            ss << "UNKNOWN";
    }
    ss << "] " << msg;
    
    write(ss.str(), type);
}

void PascalSystem::Logger::LoggerAbstract::writeFromHandler(int handler, int type, int maxBuf) {
    int readBytes;
    char buf[maxBuf];
    bzero(&buf, maxBuf);
    while ((readBytes = read(handler, &buf, maxBuf)) > 0) {
        std::string data = "";
        data.append(buf);
        data.substr(0, readBytes);
        sendMessage(data, type);
        bzero(&buf, maxBuf);
    }
}

pthread_t PascalSystem::Logger::LoggerAbstract::asyncWriteFromHandler(int handler, int type, int maxBuf) {
    ThreadLoggerStruct* structData = new ThreadLoggerStruct();
    structData->logger = this;
    structData->handler = handler;
    structData->type = type;
    structData->maxBuf = maxBuf;

    pthread_t handlerWriterThread;
    if (pthread_create(&handlerWriterThread, NULL, &handlerThreadLoggerStruct, structData) != 0) {
        std::runtime_error("Can`t create asynchronous thread for rewrite data from descriptor handler");
    }
    pthread_detach(handlerWriterThread);
    
    return handlerWriterThread;
}