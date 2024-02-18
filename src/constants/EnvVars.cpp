//
// Created by Shantanu Banerjee on 19/10/23.
//
#include "EnvVars.h"

namespace cumulus {

void EnvVars::parse_env_variables(char **argp) {
    auto _idx = 0;

    auto separate_equals = [](char *env) -> std::pair<std::string, std::string> {
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

    while (argp[_idx]) {
        auto p = separate_equals(argp[_idx]);
        if (EnvVars::_env_vars.find(p.first) == EnvVars::_env_vars.end()) {
            EnvVars::_env_vars[p.first] = std::move(p.second);
        }
        ++_idx;
    }
}

std::map<std::string, std::string> EnvVars::_env_vars = {};

}