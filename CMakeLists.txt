cmake_minimum_required(VERSION 3.22)
project(cumulus)

set(CMAKE_CXX_STANDARD 23)

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
)
target_include_directories(
        cumulus PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/connection src/constants)


target_link_libraries(cumulus sslsocketutil cpr::cpr)
