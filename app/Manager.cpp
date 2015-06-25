/* 
 * File:   Manager.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 17 maj 2015, 14:01
 */

#include "Manager.h"

void *NodePM::Manager::threadRunItem(void* data) {
    ThreadItemProcess* threadData = ((ThreadItemProcess*)data);
    threadData->item->runPermanently();
}

int NodePM::Manager::runThreadForkItem(std::string appKey, int forkCounter, PascalSystem::Process::Item* itemProc) {
    ThreadItemProcess* params = new ThreadItemProcess();
    params->key = appKey;
    params->forkNum = forkCounter;
    params->item = itemProc;

    pthread_t thread;
    int res = pthread_create(&thread, NULL, &threadRunItem, params);
    pthread_detach(thread);
    
    return res;
}

void NodePM::Manager::loadSettings(PascalSystem::Settings::SettingsAbstract* settings) {
    try {
        if (settings->exists("logErrorFilePath")) {
            logger = new PascalSystem::Logger::LoggerFileOut(
                settings->getStringValue("logErrorFilePath"),
                settings->exists("logDebugFilePath")
                    ? settings->getStringValue("logDebugFilePath")
                    : settings->getStringValue("logErrorFilePath")
            );
        }
        
        std::string globalNodePath = settings->getStringValue("appNodePath");
        std::string globalNodeArgs = settings->exists("appNodeArgs") ? settings->getStringValue("appNodeArgs") : "";

        std::list<std::string> sectiones = settings->getSectiones();
        std::list<std::string>::iterator it;
        for (it = sectiones.begin(); it != sectiones.end(); it++) {
            std::string sectionKey = (*it);
            int forkNums = settings->exists("fork", sectionKey)
                ? settings->getIntegerValue("fork", sectionKey)
                : 1;

            if (forkNums < 1) {
                throw std::runtime_error("required minimum one fork process for any item");
            }
            
            reloadTimeInterval[sectionKey] = settings->exists("reloadTimeWait", sectionKey)
                    ? settings->getIntegerValue("reloadTimeWait", sectionKey)
                    : 0;
            
            std::list<std::string> socketKeys = getListByString(
                settings->exists("socketKeys", sectionKey)
                    ? settings->getStringValue("socketKeys", sectionKey)
                    : "default"
            );
            
            PascalSystem::Logger::LoggerAbstract* itemLogger = (settings->exists("logErrorFilePath", sectionKey))
                    ? new PascalSystem::Logger::LoggerFileOut(
                            settings->getStringValue("logErrorFilePath", sectionKey),
                            settings->exists("logDebugFilePath", sectionKey)
                                ? settings->getStringValue("logDebugFilePath", sectionKey)
                                : settings->getStringValue("logErrorFilePath", sectionKey)
                        )
                    : logger;
            
            ItemFork* itemFork = new ItemFork();
            itemFork->isRunning = false;
            for (int procForkNum = 0; procForkNum < forkNums; procForkNum++) {
                std::map<std::string, std::string> socketParamsArgs;
                for (std::list<std::string>::iterator socketKeysIt = socketKeys.begin(); socketKeysIt != socketKeys.end(); socketKeysIt++) {
                    std::ostringstream ss;
                    ss << procForkNum;
                    std::string socketDefinitionType = (*socketKeysIt);
                    socketParamsArgs[socketDefinitionType] = settings->getStringValue(ss.str(), sectionKey + ".socketFilePath." + socketDefinitionType);
                }

                PascalSystem::Process::ConfigNodeJS* itemConf = createItemConfigNodeJS(settings, sectionKey, globalNodePath, globalNodeArgs);
                if (socketParamsArgs.size() > 0) {
                    itemConf->setSocketPaths(socketParamsArgs);
                }

                PascalSystem::Process::Item* item = new PascalSystem::Process::Item(itemConf, itemLogger);
                itemFork->items.push_back(item);
            }
            items[sectionKey] = itemFork;
            
            int counterTemporarySocket = 0;
            std::map<std::string, std::string> temporarySocketParamsArgs;
            for (std::list<std::string>::iterator socketKeysIt = socketKeys.begin(); socketKeysIt != socketKeys.end(); socketKeysIt++) {
                std::string socketDefinitionType = (*socketKeysIt);
                if (settings->exists(socketDefinitionType, sectionKey + ".temporarySocketFilePath")) {
                    temporarySocketParamsArgs[socketDefinitionType] = settings->getStringValue(socketDefinitionType, sectionKey + ".temporarySocketFilePath");
                    counterTemporarySocket++;
                }
            }
            if (counterTemporarySocket > 0) {
                if (counterTemporarySocket != socketKeys.size()) {
                    throw std::runtime_error("backup temporary socket numbers diffrent then socket keys");
                }
                
                PascalSystem::Process::ConfigNodeJS* backupItemConf = createItemConfigNodeJS(settings, sectionKey, globalNodePath, globalNodeArgs);
                backupItemConf->setSocketPaths(temporarySocketParamsArgs);
                
                PascalSystem::Process::Item* backupItem = new PascalSystem::Process::Item(
                    backupItemConf,
                    new PascalSystem::Logger::LoggerDevNull()
                );
                this->backupTemporaryItem[sectionKey] = backupItem;
            }
        }
    } catch (std::runtime_error &ex) {
        std::string errMsg = "Error loading settings: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    } catch (std::exception &ex) {
        std::string errMsg = "Error loading settings: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    }
}

PascalSystem::Process::ConfigNodeJS* NodePM::Manager::createItemConfigNodeJS(PascalSystem::Settings::SettingsAbstract* settings, std::string sectionKey, std::string globalNodePath, std::string globalNodeArgs) {
    PascalSystem::Process::ConfigNodeJS* itemConf = new PascalSystem::Process::ConfigNodeJS();
    
    itemConf->setNodePath(
        settings->exists("appNodePath", sectionKey)
            ? settings->getStringValue("appNodePath", sectionKey)
            : globalNodePath,
        settings->exists("appNodeArgs", sectionKey)
            ? settings->getStringValue("appNodeArgs", sectionKey)
            : globalNodeArgs);
    itemConf->setAppPath(
        settings->getStringValue("appPath", sectionKey),
        settings->exists("appArgs", sectionKey) ? settings->getStringValue("appArgs", sectionKey) : ""
    );
    itemConf->setErrorOptions(
        settings->exists("tryIntervalSecond") ? settings->getIntegerValue("tryIntervalSecond") : TRY_INTERVAL_SECOND,
        settings->exists("maxTryInInterval") ? settings->getIntegerValue("maxTryInInterval") : MAX_TRY_IN_INTERVAL,
        settings->exists("sleepTimeOnError") ? settings->getIntegerValue("sleepTimeOnError") : SLEEP_TIME_ON_ERROR
    );

    return itemConf;
}

void NodePM::Manager::waitForSocket(PascalSystem::Process::Item* item) {
    PascalSystem::Process::ConfigNodeJS* itemConf = ((PascalSystem::Process::ConfigNodeJS*)item->getConfig());
    std::map<std::string, std::string> socketArgs = itemConf->getSocketPaths();
    
    for (std::map<std::string, std::string>::iterator it = socketArgs.begin(); it != socketArgs.end(); it++) {
        do {
            if (it->second.find("/") == 0) {
                int sockTester = socket(AF_UNIX, SOCK_STREAM, 0);
                struct sockaddr_un servAddr;
                bzero((char*)&servAddr, sizeof(servAddr));
                servAddr.sun_family = AF_UNIX;
                strcpy(servAddr.sun_path, it->second.c_str());
                if (connect(sockTester, (sockaddr*)&servAddr, sizeof(servAddr)) == 0) {
                    close(sockTester);
                    break;
                }
            } else {
                int sockTester = socket(AF_INET, SOCK_STREAM, 0);
                struct sockaddr_in servAddr;
                bzero((char*)&servAddr, sizeof(servAddr));
                servAddr.sin_family = AF_INET;
                servAddr.sin_port = htons(atoi(it->second.c_str()));
                if (connect(sockTester, (sockaddr*)&servAddr, sizeof(servAddr)) == 0) {
                    close(sockTester);
                    break;
                }
            }
            usleep(50000);
        } while (true);
    }
    sleep(1);
}

void NodePM::Manager::start() {
    logger->info("Start starting application.");
    if (isStart) {
        throw std::runtime_error("Can`t start application, application is running, use restart or stop");
    }

    try {
        std::map<std::string, ItemFork*>::iterator it;
        for (it = items.begin(); it != items.end(); it++) {
            it->second->isRunning = true;
            std::list<PascalSystem::Process::Item*>::iterator forkProcIt;
            int forkCounter = 0;
            for (forkProcIt = it->second->items.begin(); forkProcIt != it->second->items.end(); forkProcIt++) {
                runThreadForkItem(it->first, forkCounter, (*forkProcIt));
                forkCounter++;
            }
        }
    } catch (std::runtime_error &ex) {
        std::string errMsg = "Error start: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    } catch (std::exception &ex) {
        std::string errMsg = "Error start: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    }
    
    logger->info("End starting application.");
    isStart = true;
}

void NodePM::Manager::stop(bool notKill) {
    if (!isStart) {
        throw std::runtime_error("Can`t stop application, application is not running, use start");
    }
    logger->info("Start stoping application.");
    
    try {
        std::map<std::string, ItemFork*>::iterator it;
        for (it = items.begin(); it != items.end(); it++) {
            it->second->isRunning = false;
            std::list<PascalSystem::Process::Item*>::iterator forkProcIt;
            for (forkProcIt = it->second->items.begin(); forkProcIt != it->second->items.end(); forkProcIt++) {
                PascalSystem::Process::Item* item = (*forkProcIt);
                item->stop();
            }
        }
    } catch (std::runtime_error &ex) {
        std::string errMsg = "Error stop: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    } catch (std::exception &ex) {
        std::string errMsg = "Error stop: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    }
    
    logger->info("End stoping application.");
    isStart = false;
    
    if (!notKill) {
        logger->info("End NodePM running.");
        exit(EXIT_SUCCESS);
    }
}

void NodePM::Manager::refreshProc(std::string appKey, bool reloadMode) {
    if (!isStart) {
        throw std::runtime_error("Can`t refresh application, application is not running, use start");
    }
    logger->info("Start refhres application.");
    
    try {
        bool foundAppKey = false;
        std::map<std::string, ItemFork*>::iterator it;
        for (it = items.begin(); it != items.end(); it++) {
            if ((appKey.length() > 0) && (it->first != appKey)) {
                continue;
            }

            PascalSystem::Process::Item* backupItem = NULL;
            if (reloadMode && (backupTemporaryItem.find(it->first) != backupTemporaryItem.end())) {
                backupItem = backupTemporaryItem[it->first];
                runThreadForkItem(it->first, -1, backupItem);
                waitForSocket(backupItem);
                
                if (reloadTimeInterval[it->first] > 0) {
                    sleep(reloadTimeInterval[it->first]);
                }
            }
            
            foundAppKey = true;
            std::list<PascalSystem::Process::Item*>::iterator forkProcIt;
            int forkCounter = 0;
            for (forkProcIt = it->second->items.begin(); forkProcIt != it->second->items.end(); forkProcIt++) {
                if (!it->second->isRunning && (appKey.length() > 0)) {
                    std::string errMsg = "Can`t refresh application `";
                    errMsg.append(appKey);
                    errMsg.append("` becouse this item not running, use start app");
                    throw std::runtime_error(errMsg);
                }
                
                PascalSystem::Process::Item* item = (*forkProcIt);
                item->stop();
                runThreadForkItem(it->first, forkCounter, (*forkProcIt));
                forkCounter++;
                
                if (reloadMode) {
                    waitForSocket((*forkProcIt));
                    if (reloadTimeInterval[it->first] > 0) {
                        sleep(reloadTimeInterval[it->first]);
                    }
                }
            }
            
            if (reloadMode && (backupItem != NULL)) {
                backupItem->stop();
            }
        }
        
        if ((appKey.length() > 0) && !foundAppKey) {
            std::string errMsg = "not found application key ";
            errMsg.append(appKey);
            errMsg.append(" for start");
            throw std::runtime_error(errMsg.c_str());
        }
    } catch (std::runtime_error &ex) {
        std::string errMsg = "Error refresh: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    } catch (std::exception &ex) {
        std::string errMsg = "Error refresh: ";
        errMsg.append(ex.what());
        logger->err(errMsg);
        throw ex;
    }
    
    logger->info("End refresh application.");
}

bool NodePM::Manager::isFileExists(std::string filePath) {
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
}

std::list<std::string> NodePM::Manager::getListByString(std::string str) {
    std::list<std::string> res;
    
    while (str.length() > 0) {
        std::size_t socketNextPos = str.find(",");
        std::string item;
        if (socketNextPos == std::string::npos) {
            item.append(str);
            str = "";
        } else {
            item.append(str.substr(0, socketNextPos));
            str = str.substr(socketNextPos + 1);
        }
        item = PascalSystem::Settings::SettingsAbstract::trim(item);
        if (item.length() == 0) {
            throw std::runtime_error("list string value required not empty string");
        }
        
        res.push_back(item);
    }
    
    return res;
}