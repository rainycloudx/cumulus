//
// Created by Shantanu Banerjee on 19/10/23.
//

#ifndef CUMULUS_ENVVARS_H
#define CUMULUS_ENVVARS_H

#include "config.h"

#include <map>
#include <string>

namespace cumulus {

class EnvVars {

public:
    static void parse_env_variables(char **argp);

    inline static std::string get(std::string var) {
        return EnvVars::_env_vars[var];
    }

public:
    static std::map<std::string, std::string> _env_vars;
};

}

#endif //CUMULUS_ENVVARS_H
