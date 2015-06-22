/* 
 * File:   SettingsIni.h
 * Author: info@pascalsystem.pl
 *
 * Created on 16 maj 2015, 17:01
 */

#ifndef PASCALSYSTEM_SETTINGS_SETTINGSINI_H
#define	PASCALSYSTEM_SETTINGS_SETTINGSINI_H

#include "SettingsAbstract.h"
#include <fstream>

namespace PascalSystem {
    namespace Settings {
        /**
         * Settings ini
         * 
         */
        class SettingsIni : public SettingsAbstract {
        public:
            /**
             * Create ini settings 
             * 
             * @param std::string filePath
             */
            SettingsIni(std::string filePath) : SettingsAbstract() {
                setFilePath(filePath);
            }
            /**
             * Load settings
             * 
             * @return void
             */
            void load();
        private:
            /**
             * Ini file path
             * 
             * @var std::string
             */
            std::string filePath;
            /**
             * Set file path
             * 
             * @param std::string filePath
             * @return void
             */
            void setFilePath(std::string filePath) {
                this->filePath = filePath;
            }
        };
    }
}

#endif	/* PASCALSYSTEM_SETTINGS_SETTINGSINI_H */

