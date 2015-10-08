/* 
 * File:   User.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 22 czerwiec 2015, 19:23
 */

#include "User.h"

std::string PascalSystem::Utils::User::getCurrentUser() {
    char buf[128];
    bzero(&buf, 128);
    if (getlogin_r(buf, 128) == 0) {
        std::string data = "";
        return data.append(buf).substr(0, strlen(buf));
    }
    return NULL;
}

