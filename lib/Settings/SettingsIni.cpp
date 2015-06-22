/* 
 * File:   SettingsIni.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 16 maj 2015, 17:01
 */

#include "SettingsIni.h"

void PascalSystem::Settings::SettingsIni::load() {
    std::ifstream f;
    f.open(filePath.c_str());
    if (!f.is_open()) {
        throw std::runtime_error("not found config file.");
    }
    int pos;
    std::string line;
    std::string parseSection = "";
    while (std::getline(f, line)) {
        line = trim(line);
        if (line.length() == 0) {
            continue;
        }
        
        pos = line.find(";");
        if (pos != std::string::npos) {
            line = line.substr(0, pos);
            line = trim(line);
        }
        if (line.length() < 3) {
            continue;
        }
        
        if ((line.substr(0,1) == "[") && (line.substr(line.length() - 1,1) == "]")) {
            parseSection = trim(line.substr(1, line.length() - 2));
        }
        
        pos = line.find("=");
        if (pos == std::string::npos) {
            continue;
        }
        std::string key = trim(line.substr(0, pos));
        if (key.length() > 0) {
            std::string fullKey = (parseSection.length() == 0) ? "" : parseSection + ".";
            fullKey.append(key);
            std::string val = (pos < line.length()) ? trim(line.substr(pos + 1)) : "";
            val = parseValue(val);
            conf.insert(std::pair<std::string, std::string>(fullKey, val));
        }
    }
    f.close();
}
