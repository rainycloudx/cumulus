//
// Created by Shantanu Banerjee on 26/09/23.
//

#include "App.h"
#include "constants/config.h"
#include "ClientThreadWorker.h"
#include "constants/EnvVars.h"
#include "ClientConnectionServer.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>
#include <array>

namespace cumulus {

App::App(int argc, char *argv[], char *argp[]) {
    EnvVars::parse_env_variables(argp);
}

App::~App() {

}

void App::run(void) {

    std::array<ClientConnectionServer, 1> servers = {
            ClientConnectionServer(constants::app_global::CUMULUS_PORT)
    };


    for (auto& server : servers) {
        server.run();
        std::cout << "Started server on PORT [" << server.getPort() << "]\n";
    }

    for (auto& server : servers) {
        server.startAcceptingConnections();
    }

    for (auto& server : servers) {
        server.terminate_thread();
    }
}

}