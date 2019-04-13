#pragma once

#include "../Actors.hpp"
#include "Hero.h"
#include "Wall.h"
#include "Zombie.h"
#include "Princess.h"
#include "Floor.h"

class Dragon : public Actor {
public:

    Dragon(int position_row,
           int position_col,
           int max_health = 50,
           int cur_health = 50,
           int damage = 10,
           int max_mana = 40,
           int cur_mana = 40);

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Move(std::vector<Actor *>, int dir = 0) override;

//    Actor *findActor(std::vector<Actor *> act, std::pair<int, int> dir = {-1, -1}) override;

    int max_mana_points_;
    int damage_;
    int cur_mana_points_;
};
