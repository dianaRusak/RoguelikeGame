#include <cstdio>
#include <fstream>
#include <iostream>

#include "../include/Config.h"

void Config::conRead() {
    std::string const_identifier;
    auto tt = 0;
    std::ifstream fin("Config.ini");
    while (!fin.eof()) {
        fin >> const_identifier >> tt;
        mp_[const_identifier] = tt;
    }
    fin.close();
}