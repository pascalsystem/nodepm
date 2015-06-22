/* 
 * File:   HelpMe.cpp
 * Author: info@pascalsystem.pl
 * 
 * Created on 25 maj 2015, 18:33
 */

#include "HelpMe.h"

std::string NodePM::HelpMe::getData() {
    std::ostringstream ss;
    
    ss << std::endl;
    ss << "NodePM HELP" << std::endl;
    ss << std::endl;
    ss << "Basic options:" << std::endl;
    ss << "    start    - start all application from config" << std::endl;
    ss << "    stop     - stop all application from config" << std::endl;
    ss << "    restart  - restart all application from config" << std::endl;
    ss << "    start    - reload all application from config" << std::endl;
    ss << std::endl;
    ss << "Application options:" << std::endl;
    ss << "    start appKey    - start application `appKey` from config" << std::endl;
    ss << "    stop appKey     - stop application `appKey` from config" << std::endl;
    ss << "    restart appKey  - restart application `appKey` from config" << std::endl;
    ss << "    start appKey    - reload application `appKey` from config" << std::endl;
    ss << std::endl;
    ss << "Running options:" << std::endl;
    ss << "    --console=command   - start NodePM with console mode" << std::endl;
    ss << "    --help              - show NodePM help" << std::endl;
    ss << std::endl;
    
    return ss.str();
}