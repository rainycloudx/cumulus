//
// Created by Shantanu Banerjee on 26/09/23.
//
#include <iostream>

#include "ssl_sockserver.h"

namespace cumulus::connection {

SSLSocketServer::SSLSocketServer(const std::string &certFile, const std::string &keyFile)
    : _socket_ptr(std::make_unique<SSLSocket>())
{
    // Load the server's certificate and private key
    if (SSL_CTX_use_certificate_file(_socket_ptr->_ctx, certFile.c_str(), SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(_socket_ptr->_ctx, keyFile.c_str(), SSL_FILETYPE_PEM) <= 0) {
        std::cerr << "Loading certificate or private key failed." << std::endl;
        exit(1);
    }
}

}