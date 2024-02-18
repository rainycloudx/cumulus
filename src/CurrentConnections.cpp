//
// Created by Shantanu Banerjee on 19/02/24.
//

#include "CurrentConnections.h"

namespace cumulus {

void CurrentConnections::addConnection(SharedP<cumulus::ClientThreadWorker> worker) {
    std::lock_guard<std::mutex> lock(CurrentConnections::connectionMapMutex);
    CurrentConnections::presentConnections[worker->getUserId()] = worker;
}

} // cumulus