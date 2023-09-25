//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_SSL_SOCKET_H
#define CUMULUS_SSL_SOCKET_H

#include <string>

#include "openssl/ssl.h"

namespace cumulus::connection {
    class SSLSocket {
    public:
        SSLSocket(unsigned int port);

        SSLSocket(const char* address, unsigned int port);

        ~SSLSocket();

        bool create();

        bool bind(int port);

        bool listen(int backlog);

        bool accept();

        bool send(const char *data, int size);

        int receive(char *buffer, int size);

        void close();

        SSL_CTX *_ctx;
        SSL *_ssl;
        int _socket_fd;
        const char* _address;
        unsigned int _port;
    };
}

#endif //CUMULUS_SSL_SOCKET_H
