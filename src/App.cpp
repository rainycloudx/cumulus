//
// Created by Shantanu Banerjee on 26/09/23.
//

#include "App.h"
#include "constants/config.h"

#include <iostream>
#include <sstream>

namespace cumulus {

App::App(int argc, char *argv[], char *argp[]) {
    parse_env_variables(argp);
}

App::~App() {

}

void App::parse_env_variables(char **argp) {
    auto _idx = 0;

    auto separate_equals = [] (char *env) -> std::pair<std::string, std::string> {
        std::stringstream s1, s2;
        auto _sidx = 0;
        while (env[_sidx] && env[_sidx] != '=') {
            s1 << env[_sidx++];
        }
        if (env[_sidx] == '=') {
            ++_sidx;
            while (env[_sidx]) {
                s2 << env[_sidx++];
            }
        }
        return std::make_pair(s1.str(), s2.str());
    };

    auto env_complete_count = 0;
    while (argp[_idx]) {
        auto p = separate_equals(argp[_idx]);
        if (p.first == constants::app_global::KEY_FILE_PATH) {
            KEY_FILE_PATH = std::move(p.second);
            ++env_complete_count;
        } else if (p.first == constants::app_global::CERT_FILE_PATH) {
            CERT_FILE_PATH = std::move(p.second);
            ++env_complete_count;
        }
        if (env_complete_count == 2) break;
        ++_idx;
    }
}

void App::run(void) {
    std::shared_ptr<connection::SSLSocketServer> server;
    try {
        server = std::make_shared<connection::SSLSocketServer>(
                static_cast<const std::string &>(CERT_FILE_PATH),
                static_cast<const std::string &>(KEY_FILE_PATH),
                constants::app_global::CUMULUS_PORT);
        server->listen(5);
        std::cout << "Server is listening" << std::endl;
    } catch (std::exception& exp) {
        std::cerr << "Unable to start the socket server \n Reason - " << exp.what() << std::endl;
        throw exp;
    }

    try {
        handle_incoming_connections(server);
    } catch (std::exception& exp) {
        std::cerr << exp.what();
        throw exp;
    }
}

void App::handle_incoming_connections(std::shared_ptr<connection::SSLSocketServer> server) {

    while (true) {
        auto client = server->accept();
        std::string msg("Hello from server\n");
        client->send(msg.c_str(), msg.size() + 1);


    }
}

}