/* 
 * File:   ConfigNodeJS.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 12 maj 2015, 21:19
 */

#include "ConfigNodeJS.h"

void PascalSystem::Process::ConfigNodeJS::prepareCommand() {
    command.clear();
    if (nodePath.length() == 0) {
        throw std::runtime_error("Node path parameter is required");
    }
    command.push_back(nodePath);
    if (nodeArgs.length() > 0) {
        command.push_back(nodeArgs);
    }
    if (appPath.length() == 0) {
        throw std::runtime_error("Node application parameter is required");
    }
    command.push_back(appPath);
    
    std::map<std::string, std::string>::iterator it;
    for (it = socketPaths.begin(); it != socketPaths.end(); it++) {
        appArgs.append((appArgs.length() == 0) ? "" : " ");
        appArgs.append("--NODEPMSOCKET:");
        appArgs.append(it->first);
        appArgs.append(":");
        appArgs.append(it->second);
    }
    if (appArgs.length() > 0) {
        command.push_back(appArgs);
    }
}