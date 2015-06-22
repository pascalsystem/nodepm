/* 
 * File:   HelpMe.h
 * Author: info@pascalsystem.pl
 *
 * Created on 25 maj 2015, 18:33
 */

#ifndef NODEPM_HELPME_H
#define	NODEPM_HELPME_H

#include <iostream>
#include <sstream>
#include <string>

namespace NodePM {
    /**
     * Help me
     * 
     */
    class HelpMe {
    public:
        /**
         * Get help data
         * 
         * @return std::string
         */
        static std::string getData();
    private:

    };
}

#endif	/* NODEPM_HELPME_H */

