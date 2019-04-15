#pragma once

#include "../Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Princess.h"
#include "Dragon.h"
#include "Wall.h"

const int FireHero = 10;

class FireBall : public Actor {
public:

    FireBall(int position_row,
             int position_col,
             int direction,
             int damage = 10);

    int dir_;
    int damage_;

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

};