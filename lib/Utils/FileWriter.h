/* 
 * File:   FileWriter.h
 * Author: info@pascalsystem.pl
 *
 * Created on 23 maj 2015, 14:39
 */

#ifndef PASCALSYSTEM_UTILS_FILEWRITER_H
#define	PASCALSYSTEM_UTILS_FILEWRITER_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctime>
#include <sstream>
#include <string.h>
#include <map>

namespace PascalSystem {
    namespace Utils {
        /**
         * File writer
         * 
         */
        class FileWriter {
        public:
            /**
             * Get instance file writter by pattern
             * 
             * @param std::string filePathPattern
             * @return PascalSystem::Utils::FileWriter*
             */
            static FileWriter* getInstance(std::string filePathPattern);
            
            /**
             * Constructor
             * 
             * @param std::string filePathPatter
             */
            FileWriter(std::string filePathPattern) {
                this->filePathPattern = filePathPattern;
                this->fd = -1;
                time(&this->timeStamp);
                this->lastTimeStamp = this->timeStamp;
                initializePatternDate();
                this->filePath = getFilePath();
            }
            /**
             * Destructor
             * 
             */
            virtual ~FileWriter() {
                closeFile();
            }
            /**
             * Put data
             * 
             * @param std::string data
             */
            void put(std::string data);
        private:
            /**
             * File path pattern
             * 
             * @var std::string
             */
            std::string filePathPattern;
            /**
             * Fie path
             * 
             * @var std::string
             */
            std::string filePath;
            /**
             * File descriptor
             * 
             * @var int
             */
            int fd;
            /**
             * Time stamp
             * 
             * @var time_t
             */
            time_t timeStamp;
            /**
             * Last time stamp
             * 
             * @var time_t
             */
            time_t lastTimeStamp;
            
            /**
             * Pattern date in file path
             * 
             * @var bool
             */
            bool patternDate;
            /**
             * Pattern date year in file path
             * 
             * @var bool
             */
            bool patternDateYear;
            /**
             * Pattern date month in file path
             * 
             * @var bool
             */
            bool patternDateMonth;
            /**
             * Pattern date dat in file path
             * 
             * @var bool
             */
            bool patternDateDay;
            /**
             * Pattern date hour in file path
             * 
             * @var bool
             */
            bool patternDateHour;
            /**
             * Pattern date minute in file path
             * 
             * @var bool
             */
            bool patternDateMinute;
            /**
             * Pattern date second in file path
             * 
             * @var bool
             */
            bool patternDateSecond;
            
            /**
             * Initialize pattern date
             * 
             * @return void
             */
            void initializePatternDate();
            
            /**
             * Close file
             * 
             * @return void
             */
            void closeFile() {
                close(fd);
                fd = -1;
            }
            /**
             * Get file path
             * 
             * @return std::string
             */
            std::string getFilePath();
        };
    }
}

#endif	/* PASCALSYSTEM_UTILS_FILEWRITER_H */

