/* 
 * File:   ProcSingleton.h
 * Author: info@pascalsystem.pl
 *
 * Created on 25 maj 2015, 20:22
 */

#ifndef PASCALSYSTEM_UTILS_PROCSINGLETON_H
#define	PASCALSYSTEM_UTILS_PROCSINGLETON_H

#include "Directory.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <stdexcept>

namespace PascalSystem {
    namespace Utils {
        /**
         * Process singleton
         * 
         */
        class ProcSingleton {
        public:
            /**
             * Constructor
             * 
             * @param std::string pidFileName
             * @param std::string pidFilePath
             */
            ProcSingleton(std::string pidFileName) {
                baseInitData(pidFileName);
                this->absolutePath = false;
                this->pidFileDirectory = PascalSystem::Utils::Directory::getLockDirectory();
            }
            /**
             * Constructor
             * 
             * @param std::string pidFileName
             * @param std::string pidFileDirectory
             */
            ProcSingleton(std::string pidFileName, std::string pidFileDirectory) {
                baseInitData(pidFileName);
                this->absolutePath = false;
                this->pidFileDirectory = pidFileDirectory;
            }
            /**
             * Constructor
             * 
             * @param std::string absolutePath
             * @param bool isAbsolute
             */
            ProcSingleton(std::string absolutePath, bool isAbsolute) {
                baseInitData(absolutePath);
                if (isAbsolute) {
                    this->absolutePath = true;
                } else {
                    this->absolutePath = false;
                    this->pidFileDirectory = PascalSystem::Utils::Directory::getLockDirectory();
                }
            }
            /**
             * Create pid
             * 
             * @param int pid
             * @return void
             */
            void createPid(int pid);
            /**
             * Destroy pid
             * 
             * @return void
             */
            void destroyPid();
            /**
             * Is active process singleton
             * 
             * @return bool
             */
            bool isActive();
        private:
            /**
             * Pid file descriptor
             * 
             * @var int
             */
            int fd;
            /**
             * Is absolute path
             * 
             * @var bool
             */
            bool absolutePath;
            /**
             * Pid file name
             * 
             * @var std::string
             */
            std::string pidFileName;
            /**
             * Pid file directory
             * 
             * @var std::string
             */
            std::string pidFileDirectory;
            /**
             * File pid data
             * 
             * @var int
             */
            int filePid;
            /**
             * File data data
             * 
             * @var std::string
             */
            std::string dataPid;
            
            /**
             * Initialize object data
             * 
             * @return 
             */
            void baseInitData(std::string pidFileName) {
                this->fd = -1;
                this->filePid = -1;
                this->absolutePath = false;
                this->pidFileName = pidFileName;
            }
            /**
             * Get lock descriptor
             * Dont create file only, open and try lock
             * 
             * @return int
             */
            int getLockDescriptor() {
                getLockDescriptor(false);
            }
            /**
             * Try create lock file descriptor
             * 
             * @param bool create
             * @return int
             */
            int getLockDescriptor(bool create);
            /**
             * Release lock file descriptor
             * 
             * @param int lockFD
             */
            void releaseLockDescriptor(int lockFD);
            /**
             * Get pid file line by process pid and data
             * 
             * @param int pid
             * @param std::string data
             * @return std::string
             */
            std::string getPidFileLine(int pid);
            /**
             * Get pid file path
             * @return 
             */
            std::string getPidFilePath() {
                if (absolutePath) {
                    return pidFileName;
                }
                return pidFileDirectory + "/" + pidFileName;
            }
        };
    }
}

#endif	/* PASCALSYSTEM_UTILS_PROCSINGLETON_H */

