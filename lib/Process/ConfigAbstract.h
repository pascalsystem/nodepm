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
         * Safe reload options
         */
        struct SafeReloadOption {
            /**
             * Safe reload mode
             * 
             * @param bool modeOn
             */
            bool modeOn;
            /**
             * Maximum number of try send signal
             */
            int maxTry;
            /**
             * Interval second betweend send signal
             */
            int interval;
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
             * Set process environments
             * 
             * @param std::string environments
             */
            void setEnvironments(std::list<std::string> environments);
            /**
             * Set safe reload options
             * 
             * @param bool modeOn
             * @param int maxTry
             * @param int interval
             */
            void setSafeReloadOptionsByParameters(bool modeOn, int maxTry, int interval);
            /**
             * Set safe reload mode
             * 
             * @param PascalSystem::Process::SafeReloadOption* options
             */
            void setSafeReloadOptions(SafeReloadOption* options);
            /**
             * Has process environments
             * 
             * @return bool
             */
            bool hasEnvironments();
            /**
             * Set process environments
             * 
             * @return std::list<std::string>
             */
            std::list<std::string> getEnvironments();
            /**
             * Has process environment by key
             * 
             * @param std::string key
             * @return bool
             */
            bool hasEnvironment(std::string key);
            /**
             * Get process environment by key
             * 
             * @param std::string key
             * @return std::string
             */
            std::string getEnvironment(std::string key);
            /**
             * Get safe reload mode
             * 
             * @return PascalSystem::Process::SafeReloadOption*
             */
            SafeReloadOption* getSafeReloadOptions();
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
             * Process environments
             * 
             * @var std::list<std::string>
             */
            std::list<std::string> environments;
            /**
             * Safe reload options
             * 
             * @var SafeReloadOption*
             */
            SafeReloadOption* safeReloadOptions;
            
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

