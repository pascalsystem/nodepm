/* 
 * File:   LoggerConsole.h
 * Author: info@pascalsystem.pl
 *
 * Created on 13 maj 2015, 21:19
 */

#ifndef PASCALSYSTEM_LOGGER_LOGGERCONSOLE_H
#define	PASCALSYSTEM_LOGGER_LOGGERCONSOLE_H

#include "LoggerAbstract.h"

namespace PascalSystem {
    namespace Logger {
        /**
         * Logger data to output console
         * 
         */
        class LoggerConsole : public LoggerAbstract {
        public:
            /**
             * Constructor
             * 
             */
            LoggerConsole() : LoggerAbstract() {
                
            };
        protected:
            /**
             * Write data to output
             * 
             * @param std::string msg
             * @param int type
             * @return void
             */
            void write(std::string msg, int type);
        private:

        };
    }
}

#endif	/* PASCALSYSTEM_LOGGER_LOGGERCONSOLE_H */

