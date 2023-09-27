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
        SSLSocketServer(const std::string& certFile, const std::string& keyFile, int port);

        std::unique_ptr<SSLSocket> accept(void);

        bool listen(int backlog);

    private:
        const std::string _certFile;
        const std::string _keyFile;
        int _server_socket_fd;
        int _port;

        void initialize_socket_server();
    };
}

#endif //CUMULUS_SSL_SOCKSERVER_H
