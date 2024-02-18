//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_APP_H
#define CUMULUS_APP_H

#include "ClientThreadWorker.h"
#include "auth/BaseAuth.h"
#include "connection/ssl_sockserver.h"

#include <string>
#include <unordered_map>
#include <mutex>

namespace cumulus {

class App {
public:
    App(int argc, char *argv[], char *argp[]);
    ~App();

    void run(void);

private:

    void handle_incoming_connections(std::shared_ptr<connection::SSLSocketServer> server);
};

}
#endif //CUMULUS_APP_H
