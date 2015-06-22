/* 
 * File:   ConfigLoader.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 22 czerwiec 2015, 22:31
 */

#include "ConfigLoader.h"

PascalSystem::Settings::SettingsIni* NodePM::ConfigLoader::getConfig() {
    return new PascalSystem::Settings::SettingsIni(getConfigPath());
}

std::string NodePM::ConfigLoader::getConfigPath() {
    std::string filePaths = "";
    
    struct passwd *pw = getpwuid(getuid());
    std::string pwDir = "";
    pwDir.append(pw->pw_dir);
    if (pwDir.length() > 0) {
        std::string dir = "";
        dir.append(pwDir);
        dir.append("/.nodepm/config.ini");
        filePaths.append(dir);
        if (isFileExists(dir)) {
            return dir;
        }
        dir = "";
        dir.append(pwDir);
        dir.append("/.nodepm.ini");
        filePaths.append(";");
        filePaths.append(dir);
        if (isFileExists(dir)) {
            return dir;
        }
    }
    std::string currentUser = PascalSystem::Utils::User::getCurrentUser();
    std::string dir = "/etc/";
    dir.append("nodepm_");
    dir.append(currentUser);
    dir.append(".ini");
    filePaths.append(";");
    filePaths.append(dir);
    if (isFileExists(dir)) {
        return dir;
    }
    dir = "/etc/nodepm.conf";
    filePaths.append(";");
    filePaths.append(dir);
    if (isFileExists(dir)) {
        return dir;
    }
    
    std::string errorMessage = "Not found config file. Create one of this file: ";
    errorMessage.append(filePaths);
    throw std::runtime_error(errorMessage.c_str());
}

bool NodePM::ConfigLoader::isFileExists(std::string filePath) {
    std::cout << filePath << std::endl;
    struct stat buffer;   
    return (stat(filePath.c_str(), &buffer) == 0);
}
