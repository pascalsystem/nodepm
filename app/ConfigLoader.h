/* 
 * File:   ConfigLoader.h
 * Author: info@pascalsystem.pl
 *
 * Created on 22 czerwiec 2015, 22:31
 */

#ifndef NODEPM_CONFIGLOADER_H
#define	NODEPM_CONFIGLOADER_H

#include "./../lib/Utils/User.h"
#include "./../lib/Settings/SettingsIni.h"
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdexcept>

namespace NodePM {
    /**
     * Config loader
     * 
     */
    class ConfigLoader {
    public:
        /**
         * Get config ini
         * 
         * @return PascalSystem::Settings::SettingsIni*
         */
        static PascalSystem::Settings::SettingsIni* getConfig();
        /**
         * Get config ini
         * 
         * @param std::string configPath
         * @return PascalSystem::Settings::SettingsIni*
         */
        static PascalSystem::Settings::SettingsIni* getConfig(std::string configPath);
    private:
        /**
         * Get config path
         * 
         * @return std::string
         */
        static std::string getConfigPath();
        /**
         * Check file exists
         * 
         * @param std::string filePath
         * @return bool
         */
        static bool isFileExists(std::string filePath);
    };
}

#endif	/* NODEPM_CONFIGLOADER_H */

