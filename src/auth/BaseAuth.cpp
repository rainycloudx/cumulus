//
// Created by Shantanu Banerjee on 09/10/23.
//

#include "BaseAuth.h"
#include "config.h"

#include <iostream>

#include "cpr/cpr.h"

namespace cumulus {

void * BaseAuth::GetUser(std::string &id_token) {
    cpr::Response resp = cpr::Post(cpr::Url { constants::app_global::getUserAuthUrl() },
            cpr::Payload {{ "idToken", id_token }});

    std::cout << resp.text << "\n";
    return nullptr;
}

}