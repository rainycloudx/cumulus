//
// Created by Shantanu Banerjee on 19/02/24.
//

#ifndef CUMULUS_CURRENTCONNECTIONS_H
#define CUMULUS_CURRENTCONNECTIONS_H

#include <mutex>
#include <unordered_map>
#include "ClientThreadWorker.h"

namespace cumulus {

class CurrentConnections {
public:

    static void addConnection(SharedP<ClientThreadWorker> worker);

    static std::mutex connectionMapMutex;
    static std::unordered_map<std::string, SharedP<ClientThreadWorker>> presentConnections;
};

} // cumulus

#endif //CUMULUS_CURRENTCONNECTIONS_H
