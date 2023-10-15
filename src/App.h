//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_APP_H
#define CUMULUS_APP_H

#include "auth/BaseAuth.h"
#include "connection/ssl_sockserver.h"
#include <string>

namespace cumulus {

class App {
public:
    App(int argc, char *argv[], char *argp[]);
    ~App();

    void run(void);

private:
    std::map<std::string, std::string> _env_vars =
            {
                    { constants::app_global::CERT_FILE_PATH_KEY, "" },
                    { constants::app_global::KEY_FILE_PATH_KEY, "" },
                    { constants::app_global::FIREBASE_WEBAPI_KEY_KEY, "" }
            };

    void parse_env_variables(char **argp);

    void handle_incoming_connections(std::shared_ptr<connection::SSLSocketServer> server);
};

}
#endif //CUMULUS_APP_H
