#pragma once

class Config {
public:
    int score_kill_D;
    int score_kill_Z;

    char identifier_bonusManaBox;

    int max_health_dragon;
    int cur_health_dragon;
    int damage_dragon;
    int max_mana_dragon;
    int cur_mana_dragon;
    char identifier_dragon;

    int damage_fireBall;
    char identifier_fireBall;

    char identifier_floor;

    int mana_damage_hero;
    int max_health_hero;
    int cur_health_hero;
    int damage_hero;
    int max_mana_hero;
    int cur_mana_hero;
    int cur_score_hero;
    char identifier_hero;

    char identifier_princess;

    char identifier_wall;

    int max_health_zombie;
    int cur_health_zombie;
    int damage_zombie;
    char identifier_zombie;

    void conRead();

};

