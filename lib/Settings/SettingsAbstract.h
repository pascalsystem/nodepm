/* 
 * File:   SettingsAbstract.h
 * Author: info@pascalsystem.pl
 *
 * Created on 16 maj 2015, 16:49
 */

#ifndef PASCALSYSTEM_SETTINGS_SETTINGSABSTRACT_H
#define	PASCALSYSTEM_SETTINGS_SETTINGSABSTRACT_H

#include <iostream>
#include <map>
#include <list>
#include <unistd.h>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <stdexcept>

namespace PascalSystem {
    namespace Settings {
        /**
         * Settings abstract class
         * 
         */
        class SettingsAbstract {
        public:
            /**
             * Left trim string
             * 
             * @param std::string s
             * @return std::string
             */
            static std::string ltrim(std::string s) {
                s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
                return s;
            }
            /**
             * Right trim string
             * 
             * @param std::string s
             * @return std::string
             */
            static std::string rtrim(std::string s) {
                s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
                return s;
            }
            /**
             * Trim string
             * 
             * @param std::string s
             * @return std::string
             */
            static std::string trim(std::string s) {
                return ltrim(rtrim(s));
            }
            
            /**
             * Constructor
             * 
             */
            SettingsAbstract() {
                
            }
            /**
             * Load settings
             * 
             * @return void
             */
            virtual void load()=0;
            /**
             * Exists settings key
             * 
             * @param std::string key
             * @return bool
             */
            bool exists(std::string key) {
                return (conf.find(key) == conf.end()) ? false : true;
            }
            /**
             * Exists settings key
             * 
             * @param std::string key
             * @param std::string sectionKey
             * @return bool
             */
            bool exists(std::string key, std::string sectionKey) {
                return exists(getFullKey(key, sectionKey));
            }
            /**
             * Get settings string value
             * 
             * @param std::string key
             * @return std::string
             */
            std::string getStringValue(std::string key);
            /**
             * Get settings integer value
             * 
             * @param std::string key
             * @return int
             */
            int getIntegerValue(std::string key);
            /**
             * Get settings string value
             * 
             * @param std::string key
             * @param std::string sectionKey
             * @return std::string
             */
            std::string getStringValue(std::string key, std::string sectionKey) {
                return getStringValue(getFullKey(key, sectionKey));
            }
            /**
             * Get settings integer value
             * 
             * @param std::string key
             * @param std::string sectionKey
             * @return int
             */
            int getIntegerValue(std::string key, std::string sectionKey) {
                return getIntegerValue(getFullKey(key, sectionKey));
            }
            /**
             * Get main section keys list
             * 
             * @return std::list<std::string>
             */
            std::list<std::string> getSectiones() {
                return getSectiones("");
            }
            /**
             * Get section keys list
             * 
             * @param std::string parentKey
             * @return std::list<std::string>
             */
            std::list<std::string> getSectiones(std::string parentKey);
        protected:
            /**
             * Get complete section value key
             * 
             * @param std::string key
             * @param std::string sectionKey
             * @return std::string
             */
            std::string getFullKey(std::string key, std::string sectionKey);
            /**
             * Parse value
             * 
             * @param std::string str
             * @return std::string
             */
            std::string parseValue(std::string str);
            
            /**
             * Settings map key and value
             * 
             * @var std::map<std::string, std::string>
             */
            std::map<std::string, std::string> conf;
        };
    }
}

#endif	/* PASCALSYSTEM_SETTINGS_SETTINGSABSTRACT_H */

