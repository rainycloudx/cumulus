//
// Created by Shantanu Banerjee on 28/09/23.
//

#ifndef CUMULUS_ERRORS_H
#define CUMULUS_ERRORS_H

#include <string>

namespace cumulus::connection {
    namespace error_strings {
        const std::string SSL_INIT_FAILED = "Cannot initialize SSL context for secure connection. Disconnecting client.";
        const std::string CERT_KEY_LOAD_FAILED = "Loading certificate or private key failed.";
    }
}
#endif //CUMULUS_ERRORS_H
