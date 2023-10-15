//
// Created by Shantanu Banerjee on 03/10/23.
//

#include "ClientThreadWorker.h"
#include "config.h"

#include <algorithm>

namespace cumulus {

ClientThreadWorker::ClientThreadWorker(std::unique_ptr<connection::SSLSocket> socket)
        : _socket(std::move(socket)) {
    handle_client_handshake();
}

bool ClientThreadWorker::isConnectCommand() {
    char buf;
    _socket->receive(&buf, 1);
    if (buf == protocol::CONNECT_CMD) {
        char buf1[protocol::CONNECTION_PARAM_LEN];
        _socket->receive(buf1, protocol::CONNECTION_PARAM_LEN);
    }
}

void ClientThreadWorker::handle_client_handshake() {
    if (isConnectCommand()) {

    }
}

}
