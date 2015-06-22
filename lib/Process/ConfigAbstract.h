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

