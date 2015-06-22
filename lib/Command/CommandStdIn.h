/* 
 * File:   CommandStdIn.h
 * Author: info@pascalsystem.pl
 *
 * Created on 20 maj 2015, 23:04
 */

#ifndef PASCALSYSTEM_COMMAND_COMMANDSTDIN_H
#define	PASCALSYSTEM_COMMAND_COMMANDSTDIN_H

#include "CommandAbstract.h"
#include <iostream>

namespace PascalSystem {
    namespace Command {
        /**
         * Command from stdin
         * 
         */
        class CommandStdIn : public CommandAbstract {
        public:
            /**
             * Constructor
             * 
             */
            CommandStdIn() : CommandAbstract() {
                
            };
        protected:
            /**
             * Get command message
             * 
             * @return std::string
             */
            std::string getMessage();
            /**
             * Send response
             * 
             * @param std::string data
             * @return void
             */
            void sendResponse(std::string data);
        private:

        };
    }
}

#endif	/* PASCALSYSTEM_COMMAND_COMMANDSTDIN_H */

