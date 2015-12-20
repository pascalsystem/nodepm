/* 
 * File:   ConfigAbstract.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 12 maj 2015, 21:16
 */

#include "ConfigAbstract.h"

void PascalSystem::Process::ConfigAbstract::setEnvironments(std::list<std::string> environments) {
    this->environments = environments;
}

void PascalSystem::Process::ConfigAbstract::setSafeReloadOptionsByParameters(bool modeOn, int maxTry, int interval) {
    PascalSystem::Process::SafeReloadOption* opts = new PascalSystem::Process::SafeReloadOption();
    opts->modeOn = modeOn;
    opts->maxTry = maxTry;
    opts->interval = interval;
    setSafeReloadOptions(opts);
}

void PascalSystem::Process::ConfigAbstract::setSafeReloadOptions(PascalSystem::Process::SafeReloadOption* safeReloadMode) {
    this->safeReloadOptions = safeReloadMode;
}

bool PascalSystem::Process::ConfigAbstract::hasEnvironments() {
    return (this->environments.size() > 0) ? true : false;
}

std::list<std::string> PascalSystem::Process::ConfigAbstract::getEnvironments() {
    return this->environments;
}

bool PascalSystem::Process::ConfigAbstract::hasEnvironment(std::string key) {
    return (getEnvironment(key).length() > 0) ? true : false;
}

std::string PascalSystem::Process::ConfigAbstract::getEnvironment(std::string key) {
    if (this->environments.size() == 0) {
        return "";
    }
    
    std::string checkStr = key;
    checkStr.append("=");
    
    std::list<std::string>::iterator it;
    for (it = this->environments.begin(); it != this->environments.end(); it++) {
        std::string envValue = (*it);
        if ((envValue.find(checkStr) == 0) && (envValue.length() > checkStr.length())) {
            return envValue.substr(checkStr.length(), envValue.length() - 1);
        }
    }
    return "";
}

PascalSystem::Process::SafeReloadOption* PascalSystem::Process::ConfigAbstract::getSafeReloadOptions() {
    return this->safeReloadOptions;
}