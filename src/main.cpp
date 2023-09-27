#include <iostream>
#include "memory"

#include "App.h"

int main(int argc, char *argv[], char *argp[]) {
    try {
        auto app_ptr = std::make_shared<cumulus::App>(argc, argv, argp);
        app_ptr->run();
    } catch (std::exception& ex) {
        std::cerr << ex.what();
    }
    return 0;
}
