#pragma once

#include "../Actors.hpp"
#include "Hero.h"
#include "Wall.h"
#include "Zombie.h"
#include "Dragon.h"
#include "Floor.h"

class Princess : public Actor {
public:

    Princess(int position_row,
             int position_col);

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Move(std::vector<Actor *>,
                       int dir) override;

//    Actor *findActor(std::vector<Actor *> act, std::pair<int, int> dir = {-1, -1}) override;

};