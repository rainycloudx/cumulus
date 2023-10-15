//
// Created by Shantanu Banerjee on 03/10/23.
//

#ifndef CUMULUS_CLIENTTHREADWORKER_H
#define CUMULUS_CLIENTTHREADWORKER_H

#include "connection/ssl_socket.h"
#include "config.h"

#include <memory>

namespace cumulus {

class ClientThreadWorker {
public:
    ClientThreadWorker(std::unique_ptr<connection::SSLSocket> socket);

private:
    void handle_client_handshake();

    bool isConnectCommand();

    Pimpl<connection::SSLSocket> _socket;

    std::string DAEMON_ID;
    std::string USER_ID;
    std::string AUTH_TOKEN;
};

}

#endif //CUMULUS_CLIENTTHREADWORKER_H
