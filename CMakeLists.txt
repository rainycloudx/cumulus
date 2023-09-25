cmake_minimum_required(VERSION 3.26)
project(cumulus)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenSSL REQUIRED)

add_executable(cumulus src/main.cpp
        src/App.cpp
        src/App.h
        src/constants/config.h
        src/connection/ssl_socket.cpp
        src/connection/ssl_socket.h
        src/connection/ssl_sockserver.cpp
        src/connection/ssl_sockserver.h)
target_link_libraries(cumulus OpenSSL::SSL OpenSSL::Crypto)
