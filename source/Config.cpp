#include <cstdio>
#include <fstream>
#include <iostream>

#include "../include/Config.h"

void Config::conRead() {
    std::string const_identifier;
    std::ifstream fin("Config.ini");
    fin >> const_identifier >> score_kill_D;
    fin >> const_identifier >> score_kill_Z;

    fin >> const_identifier >> identifier_bonusManaBox;

    fin >> const_identifier >> max_health_dragon;
    fin >> const_identifier >> cur_health_dragon;
    fin >> const_identifier >> damage_dragon;
    fin >> const_identifier >> max_mana_dragon;
    fin >> const_identifier >> cur_mana_dragon;
    fin >> const_identifier >> identifier_dragon;

    fin >> const_identifier >> damage_fireBall;
    fin >> const_identifier >> identifier_fireBall;

    fin >> const_identifier >> identifier_floor;

    fin >> const_identifier >> mana_damage_hero;
    fin >> const_identifier >> max_health_hero;
    fin >> const_identifier >> cur_health_hero;
    fin >> const_identifier >> damage_hero;
    fin >> const_identifier >> max_mana_hero;
    fin >> const_identifier >> cur_mana_hero;
    fin >> const_identifier >> cur_score_hero;
    fin >> const_identifier >> identifier_hero;

    fin >> const_identifier >> identifier_princess;

    fin >> const_identifier >> identifier_wall;

    fin >> const_identifier >> max_health_zombie;
    fin >> const_identifier >> cur_health_zombie;
    fin >> const_identifier >> damage_zombie;
    fin >> const_identifier >> identifier_zombie;
    fin.close();
}