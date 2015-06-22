/* 
 * File:   LoggerFileOut.h
 * Author: info@pascalsystem.pl
 *
 * Created on 23 maj 2015, 16:56
 */

#ifndef PASCALSYSTEM_LOGGER_LOGGERFILEOUT_H
#define	PASCALSYSTEM_LOGGER_LOGGERFILEOUT_H

#include "./../Utils/FileWriter.h"
#include "LoggerAbstract.h"
#include <iostream>

namespace PascalSystem {
    namespace Logger {
        /**
         * Logger file
         * 
         */
        class LoggerFileOut : public LoggerAbstract {
        public:
            /**
             * Constructor
             * 
             * @param std::string filePathPatternErr
             */
            LoggerFileOut(std::string filePathPatternErr) : LoggerAbstract() {
                init(filePathPatternErr, filePathPatternErr);
            }
            /**
             * Constructor
             * 
             * @param std::string filePathPatternErr
             * @parma std::string filePathPatternOut
             */
            LoggerFileOut(std::string filePathPatternErr, std::string filePathPatternOut) : LoggerAbstract() {
                init(filePathPatternErr, filePathPatternOut);
            }
            /**
             * Write data to file
             * 
             * @param std::string msg
             * @param int type
             * @return void
             */
            void write(std::string msg, int type);
        private:
            /**
             * File writer out
             * 
             * @var PascalSystem::Utils::FileWriter*
             */
            PascalSystem::Utils::FileWriter* writerOut;
            /**
             * File writer error
             * 
             * @var PascalSystem::Utils::FileWriter*
             */
            PascalSystem::Utils::FileWriter* writerErr;
            
            /**
             * Initialize
             * 
             * @param std::string filePathPatternErr
             * @param std::string filePathPatternOut
             */
            void init(std::string filePathPatternErr, std::string filePathPatternOut) {
                writerErr = PascalSystem::Utils::FileWriter::getInstance(filePathPatternErr);
                writerOut = PascalSystem::Utils::FileWriter::getInstance(filePathPatternOut);
            }
        };
    }
}

#endif	/* PASCALSYSTEM_LOGGER_LOGGERFILEOUT_H */

