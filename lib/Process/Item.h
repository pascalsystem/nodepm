/* 
 * File:   Item.h
 * Author: info@pascalsystem.pl
 *
 * Created on 12 maj 2015, 21:59
 */

#ifndef PASCALSYSTEM_PROCESS_ITEM_H
#define	PASCALSYSTEM_PROCESS_ITEM_H

#include "./../Logger/LoggerAbstract.h"
#include "ConfigAbstract.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

namespace PascalSystem {
    namespace Process {
        /**
         * Thread process output data structure
         * 
         */
        struct ThreadProcessTransmitOutput {
            /**
             * Error type
             * 
             * @var int
             */
            int type;
            /**
             * Handler
             * 
             * @var int
             */
            int handler;
            /**
             * Logger
             * 
             * @var PascalSystem::Logger::LoggerAbstract*
             */
            PascalSystem::Logger::LoggerAbstract* output;
        };
        
        /**
         * Item process
         * 
         */
        class Item {
        public:
            /**
             * Constructor
             * 
             * @param PascalSystem::Process::ConfigAbstract* config
             * @param PascalSystem::Logger::LoggerAbstract* logger
             */
            Item(ConfigAbstract* config, PascalSystem::Logger::LoggerAbstract* logger) {
                this->running = true;
                this->config = config;
                this->logger = logger;
                this->pid = -1;
            }
            /**
             * Get config item
             * 
             * @return PascalSystem::Process::ConfigAbstract*
             */
            ConfigAbstract* getConfig() {
                return config;
            }            
            /**
             * Run permanently item process
             * 
             * @return void
             */
            void runPermanently();
            /**
             * Send singnal kill to process
             * 
             * @return void
             */
            void stop();
            /**
             * Kill child process
             * 
             * @return void
             */
            void hardStop();
            /**
             * Get current pid item
             * 
             * @return int
             */
            int getPid();
        private:
            /**
             * Process pid
             * 
             * @var int
             */
            int pid;
            /**
             * Running
             * 
             * @var bool
             */
            bool running;
            /**
             * Process config
             * 
             * @var PascalSystem::Process::ConfigAbstract*
             */
            ConfigAbstract* config;
            /**
             * Item output logger
             * 
             * @var PascalSystem::Logger::LoggerAbstract*
             */
            PascalSystem::Logger::LoggerAbstract* logger;
            /**
             * Output logger thread
             * 
             * @var pthread_t
             */
            pthread_t threadOutputLogger;
            
            /**
             * Transmit output data from handler to logger
             * 
             * @param PascalSystem::Process::ThreadProcessTransmitOutput* This
             * @return void
             */
            static void *threadTransmitOutputData(void* This);

            /**
             * Run item process
             * 
             * @return void
             */
            void run();
        };
    }
}

#endif	/* PASCALSYSTEM_PROCESS_ITEM_H */

