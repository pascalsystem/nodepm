/* 
 * File:   FileWriter.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 23 maj 2015, 14:39
 */

#include "FileWriter.h"

std::map<std::string, PascalSystem::Utils::FileWriter*> ___PSFILEWRITERINSTANCES;

PascalSystem::Utils::FileWriter* PascalSystem::Utils::FileWriter::getInstance(std::string filePathPattern) {
    if (___PSFILEWRITERINSTANCES.find(filePathPattern) == ___PSFILEWRITERINSTANCES.end()) {
        ___PSFILEWRITERINSTANCES[filePathPattern] = new FileWriter(filePathPattern);
    }
    return ___PSFILEWRITERINSTANCES[filePathPattern];
}

void PascalSystem::Utils::FileWriter::put(std::string data) {
    time(&timeStamp);
    if (timeStamp > lastTimeStamp) {
        std::string timeFilePath = getFilePath();
        if (timeFilePath != filePath) {
            filePath = timeFilePath;
        }
        closeFile();
        lastTimeStamp = timeStamp;
    }
    if (fd < 0) {
        fd = open(filePath.c_str(), O_CREAT | O_APPEND | O_WRONLY, 0666);
    }
    write(fd, data.c_str(), data.length());
}

std::string PascalSystem::Utils::FileWriter::getFilePath() {
    if (!patternDate) {
        return filePathPattern;
    }
    struct tm *aTime = localtime(&timeStamp);
    std::string dateFilePath = "";
    dateFilePath.append(filePathPattern);
    
    if (patternDateYear) {
        std::ostringstream s;
        s << (aTime->tm_year + 1900);
        dateFilePath.replace(dateFilePath.find("%Y"), 2, s.str());
    }
    if (patternDateMonth) {
        std::ostringstream s;
        if (aTime->tm_mon < 9) {
            s << "0" << (aTime->tm_mon+1);
        } else {
            s << (aTime->tm_mon + 1);
        }
        dateFilePath.replace(dateFilePath.find("%M"), 2, s.str());
    }
    if (patternDateDay) {
        std::ostringstream s;
        if (aTime->tm_mday < 10) {
            s << "0" << aTime->tm_mday;
        } else {
            s << aTime->tm_mday;
        }
        dateFilePath.replace(dateFilePath.find("%D"), 2, s.str());
    }
    if (patternDateHour) {
        std::ostringstream s;
        if (aTime->tm_hour < 10) {
            s << "0" << aTime->tm_hour;
        } else {
            s << aTime->tm_hour;
        }
        dateFilePath.replace(dateFilePath.find("%H"), 2, s.str());
    }
    if (patternDateMinute) {
        std::ostringstream s;
        if (aTime->tm_min < 0) {
            s << "0" << aTime->tm_min;
        } else {
            s << aTime->tm_min;
        }
        dateFilePath.replace(dateFilePath.find("%I"), 2, s.str());
    }
    if (patternDateSecond) {
        std::ostringstream s;
        if (aTime->tm_sec < 0) {
            s << "0" << aTime->tm_sec;
        } else {
            s << aTime->tm_sec;
        }
        dateFilePath.replace(dateFilePath.find("%S"), 2, s.str());
    }
    
    return dateFilePath;
}

void PascalSystem::Utils::FileWriter::initializePatternDate() {
    patternDateYear = filePathPattern.find("%Y") != std::string::npos;
    patternDateMonth = filePathPattern.find("%M") != std::string::npos;
    patternDateDay = filePathPattern.find("%D") != std::string::npos;
    patternDateHour = filePathPattern.find("%H") != std::string::npos;
    patternDateMinute = filePathPattern.find("%I") != std::string::npos;
    patternDateSecond = filePathPattern.find("%S") != std::string::npos;
    
    patternDate = (patternDateYear || patternDateMonth || patternDateDay
            || patternDateHour || patternDateMinute || patternDateSecond);
}