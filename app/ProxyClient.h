/* 
 * File:   ProxyClient.h
 * Author: info@pascalsystem.pl
 *
 * Created on 19 maj 2015, 20:47
 */

#ifndef NODEPM_PROXYCLIENT_H
#define	NODEPM_PROXYCLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <pthread.h>

namespace NodePM {
    /**
     * Structure rewrite socket source and destination
     * 
     */
    struct StructSourceDestSocket {
        /**
         * Source
         * 
         * @var int
         */
        int source;
        /**
         * Destination
         * 
         * @var int
         */
        int dest;
        /**
         * Socket to close after finish
         * 
         * @var int
         */
        int closeSock;
    };
    
    /**
     * Proxy client
     * 
     */
    class ProxyClient {
    public:
        /**
         * Constructor
         * 
         * @param int port
         */
        ProxyClient(int port) {
            sockServerType = SOCK_STREAM;
            initPort(port);
        };
        /**
         * Constructor
         * 
         * @param int port
         * @param in_addr_t inAddr
         */
        ProxyClient(int port, in_addr_t inAddr) {
            sockServerType = SOCK_STREAM;
            initPort(port, inAddr);
        };
        /**
         * Constructor
         * 
         * @param std::string sockFilePath
         */
        ProxyClient(std::string sockFilePath) {
            sockServerType = SOCK_STREAM;
            initUnixSocket(sockFilePath);
        };
        
        /**
         * Process socket client
         * 
         * @param int sock
         * @return bool
         */
        bool process(int sock);
    private:
        /**
         * Sock server type
         * 
         * @var int
         */
        int sockServerType;
        /**
         * Destination port
         * 
         * @var int
         */
        int portDestination;
        /**
         * Address destination
         * 
         * @var in_addr_t
         */
        in_addr_t addrDestination;
        /**
         * Unix socket path destination
         * 
         * @var std::string
         */
        std::string unixSockPathDestination;
        /**
         * Flag use unix socket path
         * 
         * @var bool
         */
        bool useUnixSocket;
        
        /**
         * Rewrite data from socket to socket
         * 
         * @param NodePM::StructSourceDestSocket* This
         * @return void
         */
        static void* rewriteSocketData(void* This);
        
        /**
         * Initialize backend server destination
         * 
         * @param int port
         */
        void initPort(int port) {
            initPort(port, INADDR_LOOPBACK);
        }
        /**
         * Initialize backend server destination
         * 
         * @var int port
         */
        void initPort(int port, in_addr_t inAddr) {
            useUnixSocket = false;
            this->portDestination = port;
            this->addrDestination = inAddr;
        }
        /**
         * Initialize backend server destination
         * 
         * @param std::string sockFilePath
         */
        void initUnixSocket(std::string sockFilePath) {
            useUnixSocket = true;
            this->unixSockPathDestination = sockFilePath;
        }
    };
}

#endif	/* NODEPM_PROXYCLIENT_H */

