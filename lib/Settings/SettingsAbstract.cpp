/* 
 * File:   SettingsAbstract.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 16 maj 2015, 16:49
 */

#include "SettingsAbstract.h"

std::string PascalSystem::Settings::SettingsAbstract::getStringValue(std::string key) {
    if (conf.find(key) != conf.end()) {
        return conf[key];
    }
    std::string err = "not found value, for key: ";
    err.append(key);
    err.append(" in configuration.");
    throw std::runtime_error(err.c_str());
}

int PascalSystem::Settings::SettingsAbstract::getIntegerValue(std::string key) {
    std::string val = getStringValue(key);
    int valInt = atoi(val.c_str());
    std::stringstream ss;
    ss << valInt;
    if (ss.str() == val) {
        return valInt;
    }
    
    std::string err = "not found correct integer value, for key: ";
    err.append(key);
    err.append(" in configuration.");
    throw std::runtime_error(err.c_str());
}

std::string PascalSystem::Settings::SettingsAbstract::getFullKey(std::string key, std::string sectionKey) {
    std::string fullKey = "";
    fullKey.append(sectionKey);
    fullKey.append(".");
    fullKey.append(key);
    return fullKey;
}

std::string PascalSystem::Settings::SettingsAbstract::parseValue(std::string str) {
    int pos;
    if ((pos = str.find("{CURRENT_DIRECTORY}")) != std::string::npos) {
        std::string currentDirectory = getcwd(NULL, 0);
        str.replace(pos, 19, currentDirectory);
    }
    return str;
}

std::list<std::string> PascalSystem::Settings::SettingsAbstract::getSectiones(std::string parentKey) {
    std::list<std::string> res;
    
    std::map<std::string, std::string>::iterator it;
    for (it = conf.begin(); it != conf.end(); it++) {
        if ((parentKey.length() > 0) && (it->first.find(parentKey + ".") != 0)) {
            continue;
        }
        std::string childKey = it->first.substr((parentKey.length() > 0) ? parentKey.length() + 1 : 0);
        std::size_t foundPos = childKey.find(".");
        if (foundPos == std::string::npos) {
            continue;
        }
        std::string sectionKey = childKey.substr(0, foundPos);
        std::list<std::string>::iterator itList = std::find(res.begin(), res.end(), sectionKey);
        if (itList == res.end()) {
            res.push_back(sectionKey);
        }
    }
    
    return res;
}