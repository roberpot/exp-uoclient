//
// Created by rot on 11/10/16.
//

#include <iostream>
#include <fstream>

#include "debug.h"


std::fstream debug_file;


void _debug_init() {
    debug_file.open("debug.log", std::ios_base::out);
}

void _debug_halt() {
    debug_file.close();
}

void _debug_print(const char * buffer) {
    debug_file << buffer << std::endl;
    std::cout << buffer << std::endl;
}
