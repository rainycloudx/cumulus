//
// Created by Shantanu Banerjee on 26/09/23.
//

#include <errno.h>
#include <iostream>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ssl_sockserver.h"

namespace cumulus::connection {

SSLSocketServer::SSLSocketServer(const std::string& certFile, const std::string& keyFile, int port)
        : _certFile(certFile), _keyFile(keyFile), _port(port) {
    initialize_socket_server();
}

void SSLSocketServer::initialize_socket_server() {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    _server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket_fd == -1) {
        throw std::runtime_error("Cannot create the server socket fd. Exit");
    }

    if (::bind(_server_socket_fd, (sockaddr *) &serverAddr, sizeof(serverAddr)) != 0) {
        ::close(_server_socket_fd);
        throw std::runtime_error("Cannot bind server fd to port. Exit. errno = " + std::to_string(errno));
    }
}

bool SSLSocketServer::listen(int backlog) {
    return ::listen(_server_socket_fd, backlog) == 0;
}

std::unique_ptr<SSLSocket> SSLSocketServer::accept() {
    int clientSocket = ::accept(_server_socket_fd, 0, 0);

    if (clientSocket == -1) {
        throw std::runtime_error("Unable to accept the incoming client socket.");
    }

    return std::make_unique<SSLSocket>(_certFile, _keyFile, clientSocket);
}

}