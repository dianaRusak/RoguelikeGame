#pragma once

#include "../Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Princess.h"
#include "Dragon.h"
#include "Floor.h"
#include "FireBall.h"

class Wall : public Actor {
public:

    Wall(int position_row,
         int position_col);

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Floor *) override;


    CollideResult Collide(FireBall *) override;

    CollideResult Move(std::vector<Actor *>,
                       int dir) override;

//     Actor* findActor(std::vector<Actor*> act, std::pair<int, int> dir = {-1, -1}) override;

};
