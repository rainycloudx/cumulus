//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_CONFIG_H
#define CUMULUS_CONFIG_H

#include <memory>
#include <string>
#include <map>
#include <format>
#include <sstream>

namespace cumulus {

    template <typename T>
    using Pimpl = std::unique_ptr<T>;

    template <typename T>
    using SharedP = std::shared_ptr<T>;


    namespace constants::app_global {
        /*
         * Application related constants
         */

        const std::string CUMULUS_HOST = "localhost";
        const unsigned int CUMULUS_PORT = 54398;
        const unsigned int API_CONNECTION_SERVER_PORT = 54399;
        const std::string PROG_NAME = "Cumulus";
        const std::string KEY_FILE_PATH_KEY = "CUMULUS_KEY_FILE_PATH";
        const std::string CERT_FILE_PATH_KEY = "CUMULUS_CERT_FILE_PATH";

        /*
         * Firebase Authentication related constants
         */

        const std::string FIREBASE_WEBAPI_KEY_KEY = "FIREBASE_WEBAPI_KEY";
        const std::string FIREBASE_AUTH_BASE_URL = "https://identitytoolkit.googleapis.com/v1/accounts";
        const std::string CMD_LOOKUP = ":lookup";
        const std::string Q_KEY = "?key=";

        inline const std::string getUserAuthUrl() {
            return FIREBASE_AUTH_BASE_URL + CMD_LOOKUP + Q_KEY;
        }
    }

    namespace protocol {
        const char CONNECT_CMD = 'c';
        const size_t CONNECT_CMD_LEN = 1;
        const size_t DAEMON_ID_LEN = 32;
        const size_t AUTH_TOKEN_LEN_LEN = sizeof(char);
        const size_t AUTH_TOKEN_LEN = 32;
        const size_t CONNECTION_PARAM_LEN = DAEMON_ID_LEN + AUTH_TOKEN_LEN;
    }

    namespace connection {
        const timeval socket_read_timeout = {
                0 /* secs */,
                200 /* usecs */
        };

    }
}

#endif //CUMULUS_CONFIG_H
