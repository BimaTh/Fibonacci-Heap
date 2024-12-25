#include "../include/error_handler.h"
#include <iostream>

#include "_env.h"


void error_handler::e_log(int id) {
    if(FLAG) {
        int classID = id / 10;
        int errorID = id % 10;
        std::cerr << std::endl << errorClass[classID] + errorMessages[errorID];
    }
}
void error_handler::verbose_log(int classID, std::string msg) {
    if(FLAG) {
        std::cout << std::endl << errorClass[classID] + msg;
    }
}

