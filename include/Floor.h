#pragma once

#include "../Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Princess.h"
#include "Dragon.h"
#include "Wall.h"
#include "FireBall.h"

class Floor : public Actor {
public:

    Floor(int position_row,
          int position_col);


    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Collide(FireBall *) override;

    CollideResult Move(std::vector<Actor *> v, int dir);

};
