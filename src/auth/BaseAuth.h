//
// Created by Shantanu Banerjee on 09/10/23.
//

#ifndef CUMULUS_BASEAUTH_H
#define CUMULUS_BASEAUTH_H

#include "config.h"

#include <string>
#include <map>

namespace cumulus {

class BaseAuth {

public:
    BaseAuth(char **argp);

    virtual ~BaseAuth();

private:

};

}


#endif //CUMULUS_BASEAUTH_H
