/* 
 * File:   SocketServerPort.h
 * Author: info@pascalsystem.pl
 *
 * Created on 19 maj 2015, 19:45
 */

#ifndef PASCALSYSTEM_SOCKET_SOCKETSERVERPORT_H
#define	PASCALSYSTEM_SOCKET_SOCKETSERVERPORT_H

#include "SocketServerAbstract.h"

namespace PascalSystem {
    namespace Socket {
        /**
         * Socket server port
         * 
         */
        class SocketServerPort : public SocketServerAbstract {
        public:
            /**
             * Constructor
             * 
             * @param int port
             */
            SocketServerPort(int port) : SocketServerAbstract() {
                this->port = port;
            }
        protected:
            /**
             * Socket port
             */
            int port;
            
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
        };
    }
}

#endif	/* PASCALSYSTEM_SOCKET_SOCKETSERVERPORT_H */

