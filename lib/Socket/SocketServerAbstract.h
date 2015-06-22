/* 
 * File:   SocketServerAbstract.h
 * Author: info@pascalsystem.pl
 *
 * Created on 19 maj 2015, 18:18
 */

#ifndef PASCALSYSTEM_SOCKET_SOCKETSERVERABSTRACT_H
#define	PASCALSYSTEM_SOCKET_SOCKETSERVERABSTRACT_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>

namespace PascalSystem {
    namespace Socket {
        /**
         * Struct socket server bag for client
         * 
         */
        struct SocketServerBag {
            /**
             * Socket server
             * 
             * @var int
             */
            int socketServer;
            /**
             * Socket server custom data
             * 
             * @var void*
             */
            void* customData;
        };
        
        /**
         * Socket server
         * 
         */
        class SocketServerAbstract {
        public:
            /**
             * Constructor
             * 
             */
            SocketServerAbstract() {
                sock = -1;
                maxQueuedClients = SOMAXCONN;
                acceptedSocketHandler = NULL;
                nonBlock = true;
                nonIgnoreSinglalPipe = false;
                running = true;
                
                socketServerBag = new SocketServerBag();
                socketServerBag->socketServer = sock;
                socketServerBag->customData = NULL;
            }
            /**
             * Destructor
             * 
             */
            ~SocketServerAbstract() {
                closeSocket();
            }
            /**
             * Set accepted socket handler function
             * 
             * @var function *acceptedSocketHandler
             */   
            void setAcceptedSocketHandler(bool (*acceptedSocketHandler)(int, SocketServerBag*)) {
                this->acceptedSocketHandler = acceptedSocketHandler;
            }
            /**
             * Set custom server bag for data
             * 
             * @param void* data
             * @return void
             */
            void setCustomServerBag(void* data) {
                this->socketServerBag->customData = data;
            }
            /**
             * Initialize
             * 
             * @return void
             */
            void init() {
                if (acceptedSocketHandler == NULL) {
                    throw std::runtime_error("Pascal System socket server required set accepted socket handler, before init method");
                }
                createSocket();
                bindSocket();
                prepareSocket();
            }
            /**
             * Run socket server
             * 
             * @return void
             */
            void run() {
                if (sock <= 0) {
                    throw std::runtime_error("Pascal System run required before run call method init");
                }
                listenSocket();
            }
            /**
             * Set listen flag to stop
             * 
             * @return void
             */
            void stop() {
                running = false;
            }
            /**
             * Set maxmimum queued clients
             * 
             * @param std::string maxQueuedClients
             */
            void setMaxQueuedClients(int maxQueuedClients) {
                if (sock > 0) {
                    throw std::runtime_error("Pascal System not allowed change max queued clients after run server");
                }
                this->maxQueuedClients = maxQueuedClients;
            }
            /**
             * Set non blocking
             * 
             * @param bool nonBlock
             */
            void setNonBlock(bool nonBlock) {
                this->nonBlock = nonBlock;
            }
            /**
             * Set non ignore singnal pipe
             * 
             * @param bool nonIgnoreSinglalPipe
             */
            void setNonIgnoreSignalPipe(bool nonIgnoreSinglalPipe) {
                this->nonIgnoreSinglalPipe = nonIgnoreSinglalPipe;
            }
        protected:
            bool running;
            /**
             * Socket handler
             * 
             * @var int
             */
            int sock;
            /**
             * Maxmimum queued clients
             * 
             * @var int
             */
            int maxQueuedClients;
            /**
             * Non blocking
             * 
             * @var bool
             */
            bool nonBlock;
            /**
             * Non ignore signal pipe
             * 
             * @var bool
             */
            bool nonIgnoreSinglalPipe;
            /**
             * Socket server bag
             * 
             * @var PascalSystem::Socket::SocketServerBag*
             */
            SocketServerBag* socketServerBag;
            /**
             * Accepted socket handler
             * This function when returned true then library socket don`t close client socket
             * when returned false then library socket automatic close client socket
             * 
             * @var function *acceptedSocketHandler
             */
            bool (*acceptedSocketHandler)(int, SocketServerBag*);
            
            /**
             * Prepare socket server
             * 
             * @return void
             */
            void prepareSocket();
            /**
             * Listen on socket
             * 
             * @return void
             */
            void listenSocket();
            /**
             * Close socket server
             * 
             * @return void
             */
            void closeSocket();
            /**
             * Get accepted socket for client
             * 
             * @return int
             */
            int getAcceptedSocket();
            /**
             * Create socket server
             * 
             * @return void
             */
            virtual void createSocket()=0;
            /**
             * Bind socket server
             * 
             * @return void
             */
            virtual void bindSocket()=0;
        private:
        };
    }
}

#endif	/* PASCALSYSTEM_SOCKET_SOCKETSERVERABSTRACT_H */

