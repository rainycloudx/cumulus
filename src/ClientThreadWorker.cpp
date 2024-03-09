//
// Created by Shantanu Banerjee on 03/10/23.
//

#include "ClientThreadWorker.h"
#include "auth/BaseAuth.h"

#include <algorithm>
#include <iostream>

namespace cumulus {

ClientThreadWorker::ClientThreadWorker(Pimpl<connection::SSLSocket> socket) : _socket(std::move(socket)) {
    handle_client_handshake();
}

ClientThreadWorker::~ClientThreadWorker() {
    _socket->close();
}

bool ClientThreadWorker::isConnectCommand() {

    char buf;
    _socket->receive(&buf, 1);
    if (buf == protocol::CONNECT_CMD) {
        char buf1[4];
        _socket->receive(buf1, 4);
        unsigned int size;
        std::memcpy(&size, buf1, sizeof(size));
        char token[size];
        _socket->receive(token, size);
        std::string token_s(token, size);

        [[maybe_unused]] void * user = BaseAuth::GetUser(token_s);
    }

    // TODO - Leave authentication for now

    USER_ID = "shantanu_1234";

    return true;
}

void ClientThreadWorker::handle_client_handshake() {

    try {
        if (isConnectCommand()) {
            // TODO - Everything is well. Do next steps
        }
    } catch (std::runtime_error& err) {
        std::cerr << err.what();
        throw err;
    }
}

}
