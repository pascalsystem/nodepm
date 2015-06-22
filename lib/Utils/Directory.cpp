/* 
 * File:   Directory.cpp
 * Author: bkrolikowski
 * 
 * Created on 25 maj 2015, 21:45
 */

#include "Directory.h"

std::string PascalSystem::Utils::Directory::getProcDirectory() {
    if (const char* path = std::getenv("TMPDIR")) {
        std::string res = "";
        res.append(path);
        return path;
    }
    if (const char* path = std::getenv("TMP")) {
        std::string res = "";
        res.append(path);
        return path;
    }
    if (const char* path = std::getenv("TEMP")) {
        std::string res = "";
        res.append(path);
        return path;
    }
    if (const char* path = std::getenv("TEMPDIR")) {
        std::string res = "";
        res.append(path);
        return path;
    }
    
    std::string defaultPath = "/tmp";
    return defaultPath;
}
