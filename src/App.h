//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_APP_H
#define CUMULUS_APP_H

#include "connection/ssl_sockserver.h"
#include <string>

namespace cumulus {

class App {
public:
    App(int argc, char *argv[], char *argp[]);
    ~App();

    void run(void);

    std::string KEY_FILE_PATH;
    std::string CERT_FILE_PATH;

private:
    void parse_env_variables(char **argp);
    void handle_incoming_connections(std::shared_ptr<connection::SSLSocketServer> server);
};

}
#endif //CUMULUS_APP_H
