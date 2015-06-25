/* 
 * File:   ConfigAbstract.h
 * Author: info@pascalsystem.pl
 *
 * Created on 12 maj 2015, 21:16
 */

#ifndef PASCALSYSTEM_PROCESS_CONFIGABSTRACT_H
#define	PASCALSYSTEM_PROCESS_CONFIGABSTRACT_H

#include <iostream>
#include <list>
#include <stdexcept>

namespace PascalSystem {
    namespace Process {
        /**
         * Multi error options
         * 
         */
        struct MultiErrorOption {
            /**
             * Try interval time seconds
             * 
             * @var int
             */
            int tryIntervalSecond;
            /**
             * Maximum try in interval time seconds
             * 
             * @var int
             */
            int maxTryInInterval;
            /**
             * Sleep time on maximum try in interval time
             * 
             * @var int
             */
            int sleepTimeOnError;            
        };
        
        /**
         * Process configuration class
         * 
         */
        class ConfigAbstract {
        public:
            /**
             * Constructor
             * 
             */
            ConfigAbstract() {
                isPrepared = false;
                errorOptions = NULL;
            }
            /**
             * Get prepared command
             * 
             * @return std::list<std::string>
             */
            std::list<std::string> getCommand() {
                if (!isPrepared) {
                    prepareCommand();
                }
                return this->command;
            }
            /**
             * Set error options
             * 
             * @param int tryIntervalSecond
             * @param int maxTryInInterval
             * @param int sleepTimeOnError
             */
            void setErrorOptions(int tryIntervalSecond, int maxTryInInterval, int sleepTimeOnError) {
                errorOptions = new MultiErrorOption();
                errorOptions->tryIntervalSecond = tryIntervalSecond;
                errorOptions->maxTryInInterval = maxTryInInterval;
                errorOptions->sleepTimeOnError = sleepTimeOnError;
            }
            /**
             * Get error options
             * 
             * @return MultiErrorOption*
             */
            MultiErrorOption* getErrorOptions() {
                return errorOptions;
            }
        protected:
            /**
             * Config process command
             * 
             * @var std::list<std::string>
             */
            std::list<std::string> command;
            /**
             * Is prepared command
             * 
             * @var bool
             */
            bool isPrepared;
            /**
             * Error tru options
             * 
             * @var MultiErrorOption*
             */
            MultiErrorOption* errorOptions;
            
            /**
             * Prepare command
             * 
             * @return void
             * @throws std::runtime_error
             */
            virtual void prepareCommand()=0;
        private:
        };
    }
}

#endif	/* PASCALSYSTEM_PROCESS_CONFIGABSTRACT_H */

