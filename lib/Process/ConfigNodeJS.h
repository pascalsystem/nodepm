/* 
 * File:   ConfigNodeJS.h
 * Author: info@pascalsystem.pl
 *
 * Created on 12 maj 2015, 21:19
 */

#ifndef PASCALSYSTEM_PROCESS_CONFIGNODEJS_H
#define	PASCALSYSTEM_PROCESS_CONFIGNODEJS_H

#include "ConfigAbstract.h"
#include <iostream>
#include <map>

namespace PascalSystem {
    namespace Process {
        /**
         * NodeJS process configuration class
         * 
         */
        class ConfigNodeJS : public ConfigAbstract {
        public:
            /**
             * Constructor
             * 
             */
            ConfigNodeJS() : ConfigAbstract() {
                rotateSocket = false;
            }
            /**
             * Set node path
             * 
             * @param std::string nodePath
             */
            void setNodePath(std::string nodePath) {
                setNodePath(nodePath, "");
            }
            /**
             * Set node path and node arguments string
             * 
             * @param std::string nodePath
             * @param std::string nodeArgs
             */
            void setNodePath(std::string nodePath, std::string nodeArgs) {
                this->nodePath = nodePath;
                this->nodeArgs = nodeArgs;
            }
            /**
             * Set application path
             * 
             * @param std::string appPath
             */
            void setAppPath(std::string appPath) {
                setAppPath(appPath, "");
            }
            /**
             * Set application path and arguments
             * 
             * @param std::string appPath
             * @param std::string appArgs
             */
            void setAppPath(std::string appPath, std::string appArgs) {
                this->appPath = appPath;
                this->appArgs = appArgs;
            }
            /**
             * Set socket paths
             * 
             * @param std::map<std::string,std::string> socketPaths
             */
            void setSocketPaths(std::map<std::string,std::string> socketPaths) {
                this->socketPaths = socketPaths;
            }
            /**
             * Get socket paths
             * 
             * @return std::map<std::string,std::string>
             */
            std::map<std::string,std::string> getSocketPaths() {
                return socketPaths;
            }
            /**
             * Get error options
             * 
             * @return MultiErrorOption*
             */
            MultiErrorOption* getErrorOptions() {
                MultiErrorOption* options = ConfigAbstract::getErrorOptions();
                if (options == NULL) {
                    throw std::runtime_error("NodeJS Config Item required error options");
                }
                return options;
            }
        protected:
            /**
             * Prepare commmand
             * 
             * @return void
             * @throws std::runtime_error
             */
            void prepareCommand();
        private:
            /**
             * Node path
             * 
             * @var std::string
             */
            std::string nodePath;
            /**
             * Node arguments
             * 
             * @var std::string
             */
            std::string nodeArgs;
            /**
             * Application path
             * 
             * @var std::string
             */
            std::string appPath;
            /**
             * Application arguments
             * 
             * @var std::string
             */
            std::string appArgs;
            /**
             * Socket file path
             * 
             * @var std::map<std::string,std::string>
             */
            std::map<std::string,std::string> socketPaths;
            /**
             * Rotate socket
             * 
             * @var bool
             */
            bool rotateSocket;
        };
    }
}

#endif	/* PASCALSYSTEM_PROCESS_CONFIGNODEJS_H */

