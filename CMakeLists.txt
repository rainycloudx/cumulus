cmake_minimum_required(VERSION 3.26)
project(cumulus)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenSSL REQUIRED)

# Create the static library "libsslsocketutil.a"
add_library(sslsocketutil STATIC
        src/connection/ssl_socket.cpp
        src/connection/ssl_sockserver.cpp)

target_link_libraries(sslsocketutil PUBLIC OpenSSL::SSL PUBLIC OpenSSL::Crypto)

add_executable(cumulus src/main.cpp
        src/App.cpp)

target_include_directories(
        cumulus PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/connection src/constants
)

target_link_libraries(cumulus sslsocketutil)
