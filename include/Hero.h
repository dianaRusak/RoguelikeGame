#pragma once

#include "../Actors.hpp"
#include "Dragon.h"
#include "Wall.h"
#include "Zombie.h"
#include "Princess.h"
#include "Floor.h"
#include "FireBall.h"

const int score_kill = 10;

class Hero : public Actor {
public:

    Hero(int position_row,
         int position_col,
         int max_health = 150,
         int cur_health = 150,
         int damage = 15,
         int max_mana = 70,
         int cur_mana = 70,
         int score = 0) {
        cur_score_points_ = score;
        max_mana_points_ = max_mana;
        cur_mana_points_ = cur_mana;
        row_pos_ = position_row;
        col_pos_ = position_col;
        damage_ = damage;
        max_health_points_ = max_health;
        cur_health_points_ = cur_health;
        identifier = 'H';
    };

    int cur_score_points_;
    int max_mana_points_;
    int cur_mana_points_;
    int damage_;

    CollideResult Move(std::vector<Actor *>, int dir) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Collide(FireBall *) override;

//    Actor *findActor(std::vector<Actor *> act, std::pair<int, int> dir = {-1, -1}) override;

};
