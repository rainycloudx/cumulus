//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_CONFIG_H
#define CUMULUS_CONFIG_H


#include <string>

namespace cumulus::constants {
    namespace app_global {
        const std::string CUMULUS_HOST = "localhost";
        const unsigned int CUMULUS_PORT = 54398;
        const std::string PROG_NAME = "Cumulus";
    }

    namespace protocol {
        const char CONNECT_CMD = 'c';
        const size_t CONNECT_CMD_LEN = 1;
        const size_t DAEMON_ID_LEN = 32;
        const size_t CONNECTION_PARAM_LEN = CONNECT_CMD_LEN + DAEMON_ID_LEN;
    }
}

#endif //CUMULUS_CONFIG_H
