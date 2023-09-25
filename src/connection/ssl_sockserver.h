//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_SSL_SOCKSERVER_H
#define CUMULUS_SSL_SOCKSERVER_H

#include <memory>

#include "ssl_socket.h"

namespace cumulus::connection {
    class SSLSocketServer {
    public:
        SSLSocketServer(const std::string &certFile, const std::string &keyFile);

        std::unique_ptr<SSLSocket> _socket_ptr;
    };
}

#endif //CUMULUS_SSL_SOCKSERVER_H
