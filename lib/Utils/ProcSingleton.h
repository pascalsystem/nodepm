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
                this->fd = -1;
                this->filePid = -1;
                this->absolutePath = false;
                this->pidFileName = pidFileName;
                this->pidFileDirectory = PascalSystem::Utils::Directory::getLockDirectory();
            }
            /**
             * Constructor
             * 
             * @param std::string pidFileName
             * @param std::string pidFileDirectory
             */
            ProcSingleton(std::string pidFileName, std::string pidFileDirectory) {
                this->fd = -1;
                this->filePid = -1;
                this->absolutePath = false;
                this->pidFileName = pidFileName;
                this->pidFileDirectory = pidFileDirectory;
            }
            /**
             * Constructor
             * 
             * @param std::string absolutePath
             * @param bool isAbsolute
             */
            ProcSingleton(std::string absolutePath, bool isAbsolute) {
                this->fd = -1;
                this->filePid = -1;
                if (isAbsolute) {
                    this->absolutePath = true;
                    this->pidFileName = absolutePath;
                } else {
                    this->absolutePath = false;
                    this->pidFileName = absolutePath;
                    this->pidFileDirectory = PascalSystem::Utils::Directory::getLockDirectory();
                }
            }
            /**
             * Create pid
             * 
             * @param int pid
             * @return void
             */
            bool createPid(int pid) {
                return createPid(pid, "");
            }
            /**
             * Create pid
             * 
             * @param int pid
             * @param std::string data
             * @return bool
             */
            bool createPid(int pid, std::string data);
            /**
             * Destroy pid
             * 
             * @return void
             */
            void destroyPid();
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

