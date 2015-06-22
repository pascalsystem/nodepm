/* 
 * File:   CommandAbstract.h
 * Author: info@pascalsystem.pl
 *
 * Created on 20 maj 2015, 23:00
 */

#ifndef PASCALSYSTEM_COMMAND_COMMANDABSTRACT_H
#define	PASCALSYSTEM_COMMAND_COMMANDABSTRACT_H

#include <iostream>
#include <algorithm>
#include <string>

namespace PascalSystem {
    namespace Command {
        /**
         * Command process
         * 
         */
        class CommandAbstract {
        public:
            /**
             * Constructor
             * 
             */
            CommandAbstract() {
                setExitCommand("EXIT", true);
            }
            /**
             * Set command handler
             * 
             * @param function std::string (*handler)(std::string message)
             * @return void
             */
            void setHandler(std::string (*handler)(std::string message)) {
                this->handler = handler;
            }
            /**
             * Set exit command
             * 
             * @param std::string exitCommand
             * @return void
             */
            void setExitCommand(std::string exitCommand)  {
                setExitCommand(exitCommand, true);
            }
            /**
             * Set exit command
             * 
             * @param std::string exitCommand
             * @param bool ignoreLetterCase
             * @return void
             */
            void setExitCommand(std::string exitCommand, bool ignoreLetterCase) {
                this->exitCommand = "";
                this->exitCommand.append(exitCommand);
                if (ignoreLetterCase == true) {
                    this->exitCommandIgnoreLetterCase = true;
                    std::transform(this->exitCommand.begin(), this->exitCommand.end(), this->exitCommand.begin(), ::tolower);
                }
                this->exitCommandIgnoreLetterCase = false;
            }
            /**
             * Start command
             * 
             * @return void
             */
            void run();
            /**
             * Execute command
             * 
             * @param std::string data
             */
            std::string executeCommand(std::string cmd);
        protected:
            /**
             * Handler function
             * 
             * @var function std::string (*handler)(std::string message);
             */
            std::string (*handler)(std::string message);
            
            /**
             * Get command message
             * 
             * @return std::string
             */
            virtual std::string getMessage()=0;
            /**
             * Send response
             * 
             * @param std::string data
             * @return void
             */
            virtual void sendResponse(std::string data)=0;
        protected:
            /**
             * Exit command
             * 
             * @var std::string
             */
            std::string exitCommand;
            /**
             * Exit command ignore letter case
             * 
             * @var bool
             */
            bool exitCommandIgnoreLetterCase;
            
            /**
             * Check this command is exit
             * 
             * @param std::string msg
             * @return bool
             */
            bool isExitCommand(std::string msg) {
                if (exitCommandIgnoreLetterCase) {
                    std::string temp = "";
                    temp.append(msg);
                    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                    if (temp == exitCommand) {
                        return true;
                    }
                    return false;
                }
                
                if (msg == exitCommand) {
                    return true;
                }
                
                return false;
            }
        };
    }
}

#endif	/* PASCALSYSTEM_COMMAND_COMMANDABSTRACT_H */

