/* 
 * File:   CommandUnixSock.h
 * Author: info@pascalsystem.pl
 *
 * Created on 25 maj 2015, 18:49
 */

#ifndef PASCALSYSTEM_COMMAND_COMMANDUNIXSOCK_H
#define	PASCALSYSTEM_COMMAND_COMMANDUNIXSOCK_H

#include "CommandAbstract.h"
#include "./../Socket/SocketServerUnix.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdexcept>

namespace PascalSystem {
    namespace Command {
        /**
         * Command unix socket
         * 
         */
        class CommandUnixSock : public CommandAbstract {
        public:
            /**
             * Initialize client mode
             * 
             * @param std::string unixPath
             * @param std::string cmd
             * @return std::string
             */
            static std::string sendMessageToServer(std::string unixPath, std::string cmd);
            /**
             * Register server instance
             * 
             * @param std::string unixPath
             * @return void
             */
            static void reqisterInstance(std::string unixPath);
            /**
             * Get server instnace
             * 
             * @return PascalSystem::Command::CommandUnixSock*
             */
            static CommandUnixSock* getInstance();
            /**
             * Start command
             * 
             * @return void
             */
            void run();
        protected:
            /**
             * Get command message
             * 
             * @return std::string
             */
            std::string getMessage() {
                std::runtime_error("command unix socket server not supported getMessage method");
            }
            /**
             * Send response
             * 
             * @param std::string data
             * @return void
             */
            void sendResponse(std::string data) {
                std::runtime_error("command unix socket server not supported sendResponse method");
            }
        private:
            /**
             * Constructor
             * 
             * @param std::string unixPath
             */
            CommandUnixSock(std::string unixPath) : CommandAbstract() {
                initServerMode(unixPath);
            }
            /**
             * Unix socket server
             * 
             * @var PascalSystem::Socket::SocketServerUnix*
             */
            PascalSystem::Socket::SocketServerUnix* srv;
            
            /**
             * Handle socket data
             * 
             * @param int sock
             * @param PascalSystem::Socket::SocketServerBag* data
             * @return bool
             */
            static bool handleSocketData(int sock, PascalSystem::Socket::SocketServerBag* data);
            
            /**
             * Initialize server mode
             * 
             * @param std::string unixPath
             * @return void
             */
            void initServerMode(std::string unixPath);
        };
    }
}

#endif	/* PASCALSYSTEM_COMMAND_COMMANDUNIXSOCK_H */

