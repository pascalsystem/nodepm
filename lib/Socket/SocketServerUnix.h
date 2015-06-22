/* 
 * File:   SocketServerUnix.h
 * Author: info@pascalsystem.pl
 *
 * Created on 25 maj 2015, 18:56
 */

#ifndef PASCALSYSTEM_SOCKET_SOCKETSERVERUNIX_H
#define	PASCALSYSTEM_SOCKET_SOCKETSERVERUNIX_H

#include "SocketServerAbstract.h"
#include <iostream>
#include <sstream>
#include <string>
#include <sys/un.h>

namespace PascalSystem {
    namespace Socket {
        /**
         * Socket unix domain server
         * 
         */
        class SocketServerUnix : public SocketServerAbstract {
        public:
            /**
             * Constructor
             * 
             * @param std::string unixPath
             */
            SocketServerUnix(std::string unixPath) : SocketServerAbstract() {
                this->unixPath = unixPath;
            };
        protected:
            /**
             * Create socket server
             * 
             * @return void
             */
            void createSocket();
            /**
             * Bind socket server to port
             * 
             * @return void
             */
            void bindSocket();
        private:
            /**
             * Unix path
             * 
             * @var std::string
             */
            std::string unixPath;
        };
    }
}

#endif	/* PASCALSYSTEM_SOCKET_SOCKETSERVERUNIX_H */

