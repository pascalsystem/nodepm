/* 
 * File:   ProxyClient.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 19 maj 2015, 20:47
 */

#include "ProxyClient.h"

void* NodePM::ProxyClient::rewriteSocketData(void* This) {
    StructSourceDestSocket* dat = ((StructSourceDestSocket*)This);
    
    int bufSize = 1111;
    char buf[bufSize];
    int bytes;
    while ((bytes = read(dat->source, &buf, bufSize)) > 0) {
        if (write(dat->dest, buf, bytes) != bytes) {
            break;
        }
    }
    
    if (dat->closeSock > 0) {
        close(dat->closeSock);
    }
}

bool NodePM::ProxyClient::process(int sock) {
//    int srv;
//    int res;
//    if (useUnixSocket == true) {
//        srv = socket(AF_UNIX, sockServerType, 0);
//        
//        struct sockaddr_un sockAddrDest;
//        memset(&sockAddrDest, 0, sizeof(sockAddrDest));
//        sockAddrDest.sun_family = AF_UNIX;
//        strcpy(sockAddrDest.sun_path, unixSockPathDestination.c_str());
//        
//        res = connect(srv, (struct sockaddr*)&sockAddrDest, sizeof(sockAddrDest));
//    } else {
//        srv = socket(AF_INET, sockServerType, 0);
//        
//        struct sockaddr_in sockAddrDest;
//        memset(&sockAddrDest, 0, sizeof(sockAddrDest));
//        sockAddrDest.sin_family = AF_INET;
//        sockAddrDest.sin_addr.s_addr = htonl(addrDestination);
//        sockAddrDest.sin_port = htons(portDestination);
//        
//        res = connect(srv, (struct sockaddr*)&sockAddrDest, sizeof(sockAddrDest));
//    }
//    
//    if (res != 0) {
//        close(sock);
//        return true;
//    }
//    
////    StructSourceDestSocket* readerStruct = new StructSourceDestSocket();
////    readerStruct->source = sock;
////    readerStruct->dest = srv;
////    readerStruct->closeSock = sock;
////    
////    StructSourceDestSocket* writerStruct = new StructSourceDestSocket();
////    writerStruct->source = srv;
////    writerStruct->dest = sock;
////    readerStruct->closeSock = sock;
////    
////    pthread_t readerThread;
////    pthread_create(&readerThread, NULL, &rewriteSocketData, writerStruct);
////    pthread_detach(readerThread);
////    rewriteSocketData(readerStruct);
////    std::cout << "START WRITE" << std::endl;
////    rewriteSocketData(writerStruct);
    
    int readBytes;
    
    int bufSize = 1111;
    char buf1[bufSize];
    int bytes;
    sleep(5);
    readBytes = bytes = read(sock, &buf1, bufSize);
    write(sock, "x", 2);
    //write(srv, buf1, readBytes);
    
//    bytes = 128;
//    char buf2[bytes];
    
//    while ((readBytes = read(srv, &buf2, bytes)) > 0) {
//        std::string x = "";
//        x.append(buf2);
//        x.substr(0, readBytes);
//        std::cout << "..." << std::endl;
//        std::cout << x << std::endl;
//        std::cout << "..." << std::endl;
//        write(sock, buf2, readBytes);
//    }
    
    std::cout << "CLOSE SOCKET" << std::endl;
    close(sock);
    return true;
}
