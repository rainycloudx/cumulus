//
// Created by Shantanu Banerjee on 03/10/23.
//

#ifndef CUMULUS_CLIENTTHREADWORKER_H
#define CUMULUS_CLIENTTHREADWORKER_H

#include "connection/ssl_socket.h"
#include "config.h"

#include <memory>
#include <thread>

namespace cumulus {

class ClientThreadWorker {
public:
    ClientThreadWorker(Pimpl<connection::SSLSocket> socket);
    ~ClientThreadWorker();

private:
    void handle_client_handshake();

    bool isConnectCommand();

    Pimpl<connection::SSLSocket> _socket;

    std::string DAEMON_ID;
    std::string USER_ID;

    std::thread _current_thread_obj;

public:
    const std::string &getDaemonId() const {
        return DAEMON_ID;
    }

    const std::string &getUserId() const {
        return USER_ID;
    }

    const std::string &getAuthToken() const {
        return AUTH_TOKEN;
    }

    const std::thread &getCurrentThreadObj() const {
        return _current_thread_obj;
    }

    void setCurrentThreadObj(std::thread &&currentThreadObj) {
        _current_thread_obj = std::move(currentThreadObj);
    }

private:
    std::string AUTH_TOKEN;
};

}

#endif //CUMULUS_CLIENTTHREADWORKER_H
