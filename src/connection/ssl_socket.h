//
// Created by Shantanu Banerjee on 26/09/23.
//

#ifndef CUMULUS_SSL_SOCKET_H
#define CUMULUS_SSL_SOCKET_H

#include <string>

#include "openssl/ssl.h"
#include "../constants/config.h"


namespace cumulus::connection {
    class SSLSocket {
    public:
        SSLSocket(const std::string& certFile, const std::string& keyFile, int fd);

        SSLSocket(const char* address, unsigned int port);

        ~SSLSocket();

        bool create();

        bool bind(int port);

        bool listen(int backlog);

        bool accept();

        [[maybe_unused]] int setRecvTimeout(timeval timeout = socket_read_timeout) const;

        int send(const char *data, int size) const;

        int receive(char *buffer, int size) const;

        void close();

        SSL_CTX *_ctx;
        SSL *_ssl;
        int _socket_fd;
        const char* _address;
        unsigned int _port;

    private:
        void initialize_ssl(const std::string& certFile, const std::string& keyFile);
    };
}

#endif //CUMULUS_SSL_SOCKET_H
