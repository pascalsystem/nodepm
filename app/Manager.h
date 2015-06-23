/* 
 * File:   Manager.h
 * Author: info@pascalsystem.pl
 *
 * Created on 17 maj 2015, 14:01
 */

#ifndef APP_NODEPM_MANAGER_H
#define	APP_NODEPM_MANAGER_H

#include "./../lib/Logger/LoggerFileOut.h"
#include "./../lib/Logger/LoggerConsole.h"
#include "./../lib/Logger/LoggerAbstract.h"
#include "./../lib/Settings/SettingsAbstract.h"
#include "./../lib/Settings/SettingsIni.h"
#include "./../lib/Process/Item.h"
#include "./../lib/Process/ConfigNodeJS.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <map>
#include <list>
#include <pthread.h>


namespace NodePM {
    /**
     * Structure item process thread
     * 
     */
    struct ThreadItemProcess {
        /**
         * Process key name
         * 
         * @var std::string
         */
        std::string key;
        /**
         * Fork number process
         * 
         * @var int
         */
        int forkNum;
        /**
         * Process item
         * 
         * @var PascalSystem::Process::Item*
         */
        PascalSystem::Process::Item* item;
    };
    /**
     * Item forks
     * 
     */
    struct ItemFork {
        /**
         * Is running flag
         * 
         * @var bool
         */
        bool isRunning;
        /**
         * Items
         * 
         * @var std::list<PascalSystem::Process::Item*>
         */
        std::list<PascalSystem::Process::Item*> items;
    };
    
    /**
     * Node process manager
     * 
     */
    class Manager {
    public:
        /**
         * Constructor
         * 
         * @param PascalSystem::Settings::SettingsAbstract settings
         */
        Manager(PascalSystem::Settings::SettingsAbstract* settings) {
            this->logger = new PascalSystem::Logger::LoggerConsole();
            this->isStart = false;

            loadSettings(settings);
        }
        /**
         * Start all application
         * 
         * @return void
         */
        void start();
        /**
         * Stop all application
         * 
         * @return void
         */
        void stop() {
            stop(false);
        }
        /**
         * Stop all application and not kill manager
         * 
         * @param bool notKill
         * @return void
         */
        void stop(bool notKill);
        /**
         * Restart all aplication
         * 
         * @param std::string appKey
         * @return void
         */
        void restart() {
            restart("");
        }
        /**
         * Restart aplication key
         * 
         * @param std::string appKey
         * @return void
         */
        void restart(std::string appKey) {
            refreshProc(appKey, false);
        }
        /**
         * Reload all application
         * 
         * @return void
         */
        void reload() {
            return reload("");
        }
        /**
         * Reload application key
         * 
         * @param appKey
         * @return void
         */
        void reload(std::string appKey) {
            refreshProc(appKey, true);
        }
    private:
        /**
         * Flag manager is started
         * 
         * @var bool
         */
        bool isStart;
        /**
         * Process item maps
         * 
         * @var std::map<std::string, NodePM::ItemFork*>
         */
        std::map<std::string, ItemFork*> items;
        /**
         * Backup temporary process item maps
         * 
         * @var std::map<std::string, PascalSystem::Process::Item*>
         */
        std::map<std::string, PascalSystem::Process::Item*> backupTemporaryItem;
        /**
         * Extend time wait for reload
         * 
         * @var std::map<std::string, int>
         */
        std::map<std::string, int> reloadTimeInterval;
        /**
         * Manager logger
         * 
         * @var PascalSystem::Logger::LoggerAbstract*
         */
        PascalSystem::Logger::LoggerAbstract* logger;
        
        /**
         * Thread run item
         * 
         * @param NodePM::ThreadItemProcess* data
         * @return void
         */
        static void *threadRunItem(void* data);
        
        /**
         * Run fork item in thread
         * 
         * @param std::string appKey
         * @param int forkCounter
         * @param PascalSystem::Process::Item* it
         * @return int
         */
        int runThreadForkItem(std::string appKey, int forkCounter, PascalSystem::Process::Item* itemProc);
        /**
         * Load settings
         * 
         * @param PascalSystem::Settings::SettingsAbstract settings
         * @retuen void
         */
        void loadSettings(PascalSystem::Settings::SettingsAbstract* settings);
        /**
         * Create NodeJS Item configuration
         * 
         * @param PascalSystem::Settings::SettingsAbstract* settings
         * @param std::string sectionKey
         * @param std::string globalNodePath
         * @param std::string globalNodeArgs
         * @return PascalSystem::Process::ConfigNodeJS*
         */
        PascalSystem::Process::ConfigNodeJS* createItemConfigNodeJS(PascalSystem::Settings::SettingsAbstract* settings, std::string sectionKey, std::string globalNodePath, std::string globalNodeArgs);
        /**
         * Wait for item process open sockets from configurationes
         * 
         * @param PascalSystem::Process::Item* item
         */
        void waitForSocket(PascalSystem::Process::Item* item);
        /**
         * Refresh processing
         * 
         * @param std::string appKey
         * @param bool reloadMode
         * @return void
         */
        void refreshProc(std::string appKey, bool reloadMode);
        /**
         * Check file is exists
         * 
         * @param std::string filePath
         * @return bool
         */
        bool isFileExists(std::string filePath);
        /**
         * Get string list by string value
         * 
         * @param std::string str
         * @return std::string
         */
        std::list<std::string> getListByString(std::string str);
    };
}

#endif	/* APP_NODEPM_MANAGER_H */

