#pragma once

#include <map>

class Config {
public:

    std::map<std::string, int> mp_{
            {"score_kill_D",              0},
            {"score_kill_Z",              0},
            {"identifier_bonusManaBox",   0},
            {"identifier_bonusHealthBox", 0},
            {"hp_bonus_hero",             0},

            {"max_health_dragon",         0},
            {"cur_health_dragon",         0},
            {"damage_dragon",             0},
            {"max_mana_dragon",           0},
            {"cur_mana_dragon",           0},
            {"identifier_dragon",         0},

            {"damage_fireBall",           0},
            {"identifier_fireBall",       0},

            {"identifier_floor",          0},

            {"mana_damage_hero",          0},
            {"max_health_hero",           0},
            {"cur_health_hero",           0},
            {"damage_hero",               0},
            {"max_mana_hero",             0},
            {"cur_mana_hero",             0},
            {"cur_score_hero",            0},
            {"identifier_hero",           0},

            {"identifier_princess",       0},

            {"identifier_wall",           0},

            {"max_health_zombie",         0},
            {"cur_health_zombie",         0},
            {"damage_zombie",             0},
            {"identifier_zombie",         0},
    };

    void conRead();

};

