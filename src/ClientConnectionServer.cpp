//
// Created by Shantanu Banerjee on 04/11/23.
//

#include <iostream>
#include "ClientConnectionServer.h"
#include "ClientThreadWorker.h"
#include "CurrentConnections.h"
#include "EnvVars.h"

namespace cumulus {

std::mutex ClientConnectionServer::connectionMapMutex;
std::unordered_map<std::string, SharedP<ClientThreadWorker>> ClientConnectionServer::presentConnections;

ClientConnectionServer::ClientConnectionServer(int port) : port(port) {}

void ClientConnectionServer::run() {
    try {
        server = std::make_shared<connection::SSLSocketServer>(
                static_cast<const std::string>(EnvVars::get(constants::app_global::CERT_FILE_PATH_KEY)),
                static_cast<const std::string>(EnvVars::get(constants::app_global::KEY_FILE_PATH_KEY)),
                port);
        server->listen(5);
        std::cout << "Server is listening on port" << port << "\n";
    } catch (std::exception& exp) {
        std::cerr << "Unable to start the socket server \n Reason - " << exp.what() << "\n";
        throw exp;
    }
}

void ClientConnectionServer::startAcceptingConnections() {
    auto worker = SharedP<ClientThreadWorker>(nullptr);

    while (true) {
        auto client = getServer()->accept();

        /*
         * This needs to be moved inside the thread to avoid blocking of other callers.
         * Keeping this outside to just make it work for now.
         */
        worker = std::make_shared<ClientThreadWorker>(std::move(client));
        std::thread t([&]() {
            try {
                /* Ultimately we will end up in a K8S environment.
                 * So there will be a redis cache that will store the user ids -> pods;
                 * Currently we only have 1. In the future, we will need to store this `worker.getUserId()`
                 * in the cache.
                 * For now storing this in this app only. In a map<user id, worker>
                 */
                ClientConnectionServer::addConnection(worker);

            } catch (std::runtime_error& ex) {
                std::cerr << ex.what() << "\n";
                return;
            }
        });

        /*
         * Set the thread object inside the worker object to gracefully join the thread
         * and handle error conditions.
         */
        {
            worker->setCurrentThreadObj(std::move(t));
        }

    }
}

void ClientConnectionServer::addConnection(SharedP<cumulus::ClientThreadWorker> worker) {
    std::lock_guard<std::mutex> lock(ClientConnectionServer::connectionMapMutex);
    ClientConnectionServer::presentConnections[worker->getUserId()] = worker;
}

} // cumulus