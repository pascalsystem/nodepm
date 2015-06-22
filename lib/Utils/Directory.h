/* 
 * File:   Directory.h
 * Author: bkrolikowski
 *
 * Created on 25 maj 2015, 21:45
 */

#ifndef DIRECTORY_H
#define	DIRECTORY_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

namespace PascalSystem {
    namespace Utils {
        /**
         * Directory utils
         * 
         */
        class Directory {
        public:
            /**
             * Get lock files directory
             * 
             * @return std::string
             */
            static std::string getLockDirectory() {
                return getProcDirectory();
            }
            /**
             * Get sockets files directory
             * 
             * @return std::string
             */
            static std::string getSockDirectory() {
                return getProcDirectory();
            }
        private:
            /**
             * Get process directory
             * 
             * @return std::string
             */
            static std::string getProcDirectory();
        };
    }
}

#endif	/* DIRECTORY_H */

