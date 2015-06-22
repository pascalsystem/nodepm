/* 
 * File:   User.h
 * Author: info@pascalsystem.pl
 *
 * Created on 22 czerwiec 2015, 19:23
 */

#ifndef PASCALSYSTEM_UTILS_USER_H
#define	PASCALSYSTEM_UTILS_USER_H

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

namespace PascalSystem {
    namespace Utils {
        /**
         * User system
         * 
         */
        class User {
        public:
            /**
             * Get current system user name
             * 
             * @return std::string
             */
            static std::string getCurrentUser();
        private:

        };
    }
}

#endif	/* PASCALSYSTEM_UTILS_USER_H */

