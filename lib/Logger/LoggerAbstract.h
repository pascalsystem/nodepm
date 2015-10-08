/* 
 * File:   LoggerAbstract.h
 * Author: info@pascalsystem.pl
 *
 * Created on 12 maj 2015, 22:13
 */

#ifndef PASCALSYSTEM_LOGGER_LOGGERABSTRACT_H
#define	PASCALSYSTEM_LOGGER_LOGGERABSTRACT_H

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdexcept>
#include <pthread.h>

namespace PascalSystem {
    namespace Logger {
        /**
         * Thread logger struct
         * 
         */
        struct ThreadLoggerStruct {
            /**
             * Logger object
             * 
             * @var PascalSystem::Logger::LoggerAbstract*
             */
            void* logger;
            /**
             * Handler
             * 
             * @var int
             */
            int handler;
            /**
             * Type logger
             * 
             * @var int
             */
            int type;
            /**
             * Maximum buffer size
             * 
             * @var int
             */
            int maxBuf;
        };
        
        /**
         * Logger abstract class
         * 
         */
        class LoggerAbstract {
        public:
            /**
             * Type error
             * 
             * @static int
             */
            static const int LOG_TYPE_ERR = 0;
            /**
             * Type info
             * 
             * @static int
             */
            static const int LOG_TYPE_INFO = 1;
            
            /**
             * Constructor
             * 
             */
            LoggerAbstract() {
                logDateTimeFormat = "%Y-%m-%dT%H:%M:%S %z";
            }
            /**
             * Set log date time format
             * 
             * @param std::string logDateTimeFormat
             * @return void
             */
            void setLogDateTimeFormat(std::string logDateTimeFormat) {
                this->logDateTimeFormat = logDateTimeFormat.c_str();
            }
            /**
             * Write error
             * 
             * @param std::string msg
             * @return void
             */
            void err(std::string msg) {
                sendMessage(msg, LOG_TYPE_ERR);
            }
            /**
             * Write info
             * 
             * @param std::string msg
             * @return void
             */
            void info(std::string msg) {
                sendMessage(msg, LOG_TYPE_INFO);
            }
            /**
             * Set auto handler logger
             * Working until handler can readable
             * 
             * @param int handler
             * @param int type
             * @return void
             */
            void writeFromHandler(int handler, int type) {
                writeFromHandler(handler, type, 8192);
            }
            /**
             * Set auto handler logger
             * Working until handler can readable
             * 
             * @param int handler
             * @param int type
             * @param int maxBuf
             * @return void
             */
            void writeFromHandler(int handler, int type, int maxBuf);
            /**
             * Asynchronous write from handler
             * 
             * @param int handler
             * @param int type
             * @return pthred_t
             */
            pthread_t asyncWriteFromHandler(int handler, int type) {
                return asyncWriteFromHandler(handler, type, 8192);
            }
            /**
             * Asynchronous write from handler
             * 
             * @param int handler
             * @param int type
             * @return pthred_t
             */
            pthread_t asyncWriteFromHandler(int handler, int type, int maxBuf);
        protected:
            /**
             * Log date time format
             * 
             * @var const char*
             */
            const char* logDateTimeFormat;
            
            /**
             * Handler thread logger struct
             * 
             * @param PascalSystem::Logger::ThreadLoggerStruct* data
             */
            static void* handlerThreadLoggerStruct(void* data);
            
            /**
             * Get log time string
             * 
             * @return std::string
             */
            std::string getLogTime();
            /**
             * Write log
             * 
             * @param std::string msg
             * @param int type
             * @return void
             */
            virtual void write(std::string msg, int type)=0;
        private:
            /**
             * Send message to write logger
             * 
             * @param std::string msg
             * @param int type
             * @return std::string
             */
            void sendMessage(std::string msg, int type);
        };
        
        /**
         * Logger dev null
         * 
         */
        class LoggerDevNull : public LoggerAbstract {
        public:
            /**
             * Constructor
             * 
             */
            LoggerDevNull() : LoggerAbstract() {
                
            }
            /**
             * Write log
             * 
             * @param std::string msg
             * @param int type
             * @return void
             */
            void write(std::string msg, int type) {
                
            }
        };
    }
}

#endif	/* PASCALSYSTEM_LOGGER_LOGGERABSTRACT_H */

