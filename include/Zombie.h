#pragma once

#include "../Actors.hpp"
#include "Hero.h"
#include "Wall.h"
#include "Dragon.h"
#include "Princess.h"
#include "Floor.h"

class Zombie : public Actor {
public:

    Zombie(
            int position_row,
            int position_col,
            int max_health = 30,
            int cur_health = 30,
            int damage = 5,
            int max_mana = 30,
            int cur_mana = 30);

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Move(std::vector<Actor *>,
                       int dir = 0) override;

//    Actor* findActor(std::vector<Actor*> act, std::pair<int, int> dir = {-1, -1}) override;

    int damage_;
    int max_mana_points_;
    int cur_mana_points_;
};

