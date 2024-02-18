cmake_minimum_required(VERSION 3.22)
project(cumulus)

#set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

find_package(OpenSSL REQUIRED)

# Create the static library "libsslsocketutil.
add_library(sslsocketutil STATIC
        src/connection/ssl_socket.cpp
        src/connection/ssl_sockserver.cpp)

target_link_libraries(sslsocketutil PUBLIC OpenSSL::SSL PUBLIC OpenSSL::Crypto)

# Create the cumulus executable daemon
add_executable(cumulus
        src/main.cpp
        src/App.cpp
        src/ClientThreadWorker.cpp
        src/auth/BaseAuth.cpp
        src/constants/EnvVars.cpp
        src/ClientConnectionServer.cpp
        src/CurrentConnections.cpp
)
target_include_directories(
        cumulus PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/connection src/constants)

set(CMAKE_CXX_FLAGS "-v")
target_link_libraries(cumulus sslsocketutil cpr::cpr)
