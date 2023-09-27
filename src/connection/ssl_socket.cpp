//
// Created by Shantanu Banerjee on 26/09/23.
//

#include "ssl_socket.h"

#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "../constants/errors.h"

namespace cumulus::connection {

SSLSocket::SSLSocket(const std::string& certFile, const std::string& keyFile, int fd)
        : _ctx(nullptr), _ssl(nullptr), _socket_fd(fd) {
    initialize_ssl(certFile, keyFile);
}

void SSLSocket::initialize_ssl(const std::string& certFile, const std::string& keyFile) {
    SSL_load_error_strings();
    ERR_load_crypto_strings();

    OpenSSL_add_all_algorithms();
    SSL_library_init();

    _ctx = SSL_CTX_new(SSLv23_method());
    if (!_ctx) {
        throw std::runtime_error(error_strings::SSL_INIT_FAILED);
    }

    if (SSL_CTX_use_certificate_file(_ctx, certFile.c_str(), SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(_ctx, keyFile.c_str(), SSL_FILETYPE_PEM) <= 0) {
        throw std::runtime_error(error_strings::CERT_KEY_LOAD_FAILED);
    }

    _ssl = SSL_new(_ctx);
    if (!_ssl) {
        throw std::runtime_error(error_strings::SSL_INIT_FAILED);
    }

    SSL_set_fd(_ssl, _socket_fd);

    if (SSL_accept(_ssl) <= 0) {
        throw std::runtime_error(error_strings::SSL_INIT_FAILED);
    }
}

SSLSocket::~SSLSocket() {
    close();
    if (_ctx) SSL_CTX_free(_ctx);
}

int SSLSocket::send(const char *data, int size) {
    int totalSent = 0;
    while (size > 0) {
        int _sent = SSL_write(_ssl, data + totalSent, size);
        totalSent += _sent;
        size -= _sent;
    }
    return totalSent;
}

int SSLSocket::receive(char *buffer, int size) {
    int totalRecvd = 0;
    while (size > 0) {
        int _recvd = SSL_read(_ssl, buffer + totalRecvd, size);
        totalRecvd += _recvd;
        size -= _recvd;
    }
    return totalRecvd;
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

