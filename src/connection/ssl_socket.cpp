//
// Created by Shantanu Banerjee on 26/09/23.
//

#include "ssl_socket.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

namespace cumulus::connection {

SSLSocket::SSLSocket(unsigned int port)
        : _ctx(nullptr), _ssl(nullptr), _socket_fd(-1), _port(port) {
    SSL_library_init();
    SSL_load_error_strings();

    _ctx = SSL_CTX_new(SSLv23_method());
    if (!_ctx) {
        std::cerr << "SSL_CTX_new failed." << std::endl;
        exit(1);
    }

    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd != -1) {
        std::cerr << "socket fd creation failed failed." << std::endl;
        exit(1);
    }
}

SSLSocket::SSLSocket(const char* address, unsigned int port)
        : SSLSocket(port) {

    _address = address;

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    serverAddr.sin_addr.s_addr = inet_addr(_address);

}


SSLSocket::~SSLSocket() {
    close();
    if (_ctx) SSL_CTX_free(_ctx);
}

bool SSLSocket::bind(int port) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    return ::bind(_socket_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == 0;
}

bool SSLSocket::listen(int backlog) {
    return ::listen(_socket_fd, backlog) == 0;
}

bool SSLSocket::accept() {
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket = ::accept(_socket_fd, (struct sockaddr *) &clientAddr, &clientAddrLen);

    if (clientSocket == -1) {
        return false;
    }

    // Create an SSL object and associate it with the client socket
    _ssl = SSL_new(_ctx);
    if (!_ssl) {
        return false;
    }
    SSL_set_fd(_ssl, clientSocket);

    // Perform the SSL handshake
    if (SSL_accept(_ssl) <= 0) {
        return false;
    }

    _socket_fd = clientSocket;
    return true;
}

bool SSLSocket::send(const char *data, int size) {
    return SSL_write(_ssl, data, size) > 0;
}

int SSLSocket::receive(char *buffer, int size) {
    return SSL_read(_ssl, buffer, size);
}

void SSLSocket::close() {
    if (_ssl) {
        SSL_shutdown(_ssl);
        SSL_free(_ssl);
        _ssl = nullptr;
    }
    if (_socket_fd != -1) {
        ::close(_socket_fd);
        _socket_fd = -1;
    }
}



}

