//
// Created by Shantanu Banerjee on 04/11/23.
//

#ifndef CUMULUS_CLIENTCONNECTIONSERVER_H
#define CUMULUS_CLIENTCONNECTIONSERVER_H

#include <unordered_map>
#include "ServerConnectionConfigWrapper.h"
#include "ClientThreadWorker.h"

namespace cumulus {

class ClientConnectionServer : public ServerConnectionConfigWrapper {
public:
    ClientConnectionServer(int port);

    void startAcceptingConnections();

    void run();

    const SharedP<cumulus::connection::SSLSocketServer> &getServer() const {
        return server;
    }

    inline int getPort() const {
        return port;
    }

    inline void terminate_thread() {
        th.join();
    }

private:
    SharedP<connection::SSLSocketServer> server;
    std::thread th;
    int port;
    std::promise<std::exception_ptr> excp;
};

} // cumulus

#endif //CUMULUS_CLIENTCONNECTIONSERVER_H
